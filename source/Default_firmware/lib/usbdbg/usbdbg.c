/*
 * usbdbg.c
 *
 *  Created on: Jun 20, 2017
 *      Author: govind.mukundan
 */

// Debug over USB-CDC, tx only for now
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include <ft900.h>
#include <ft900_usb.h>
#include <ft900_usb_cdc.h>
#include "usbdbg.h"
// #include <panl_app.h>

/* CDC Configuration */

/* LOCAL VARIABLES *****************************************************************/

/**
 @name string_descriptor
 @brief Table of USB String descriptors

 This is placed at a fixed location in the const section allowing
 up-to 256 bytes of string descriptors to be defined. These can be
 modified or replaced by a utility or binary editor without
 requiring a recompilation of the firmware.
 They are placed at offset 0x100 and reserve 0x100 bytes.
 The data is not stored in section and is therefore
 regarded as const.
 */
DESCRIPTOR_QUALIFIER /*__at(STRING_DESCRIPTOR_LOCATION)*/ uint8_t string_descriptor[STRING_DESCRIPTOR_ALLOCATION] =
    {
        // String 0 is actually a list of language IDs supported by the real strings.
        0x04, USB_DESCRIPTOR_TYPE_STRING, 0x09,
        0x04, // 0409 = English (US)

        // String 1 (Manufacturer): "FTDI"
        0x0a, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, 'D',
        0x00, 'I', 0x00,
#if defined(__FT930__)
        // String 2 (Product): "FT930 CDCACM"
        0x1C, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, '9', 0x00, '3',
        0x00, '0', 0x00, ' ', 0x00, 'C', 0x00, 'D', 0x00, 'C', 0x00, ' ', 0x00,
        'A', 0x00, 'C', 0x00, 'M', 0x00,
#else
        // String 2 (Product): "FT900 CDCACM"
        0x1C, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, '9',
        0x00, '0', 0x00, '0', 0x00, ' ', 0x00, 'C', 0x00, 'D', 0x00,
        'C', 0x00, ' ', 0x00, 'A', 0x00, 'C', 0x00, 'M', 0x00,
#endif

        // String 3 (Serial Number): "FT424242"
        0x12, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, '4',
        0x00, '2', 0x00, '4', 0x00, '2', 0x00, '4', 0x00, '2', 0x00,

#if defined(__FT930__)
        // String 4 (DFU Product Name): "FT930 DFU Mode"
        0x1E, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, '9', 0x00, '3',
        0x00, '0', 0x00, ' ', 0x00, 'D', 0x00, 'F', 0x00, 'U', 0x00, ' ', 0x00,
        'M', 0x00, 'o', 0x00, 'd', 0x00, 'e', 0x00,
#else
        // String 4 (DFU Product Name): "FT900 DFU Mode"
        0x1E, USB_DESCRIPTOR_TYPE_STRING, 'F', 0x00, 'T', 0x00, '9',
        0x00, '0', 0x00, '0', 0x00, ' ', 0x00, 'D', 0x00, 'F', 0x00,
        'U', 0x00, ' ', 0x00, 'M', 0x00, 'o', 0x00, 'd', 0x00, 'e',
        0x00,
#endif

        // String 5 (Interface Name): "DFU Interface"
        0x1c, USB_DESCRIPTOR_TYPE_STRING, 'D', 0x00, 'F', 0x00, 'U',
        0x00, ' ', 0x00, 'I', 0x00, 'n', 0x00, 't', 0x00, 'e', 0x00,
        'r', 0x00, 'f', 0x00, 'a', 0x00, 'c', 0x00, 'e', 0x00,

        // END OF STRINGS
        0x00};

/**
 @name wcid_string_descriptor
 @brief USB String descriptor for WCID identification.
 */
DESCRIPTOR_QUALIFIER uint8_t wcid_string_descriptor[USB_MICROSOFT_WCID_STRING_LENGTH] =
    {USB_MICROSOFT_WCID_STRING(WCID_VENDOR_REQUEST_CODE)};

/**
 @name device_descriptor_cdcacm
 @brief Device descriptor for Run Time mode.
 */
DESCRIPTOR_QUALIFIER USB_device_descriptor device_descriptor_cdcacm = {
    0x12,                                      /* bLength */
    USB_DESCRIPTOR_TYPE_DEVICE,                /* bDescriptorType */
    USB_BCD_VERSION_2_0, /* bcdUSB */          // V2.0
    USB_CLASS_DEVICE, /* bDeviceClass */       // Defined in interface
    USB_SUBCLASS_DEVICE, /* bDeviceSubClass */ // Defined in interface
    USB_PROTOCOL_DEVICE, /* bDeviceProtocol */ // Defined in interface
    USB_CONTROL_EP_MAX_PACKET_SIZE,            /* bMaxPacketSize0 */
    USB_VID_FTDI, /* idVendor */               // idVendor: 0x0403 (FTDI)
    USB_PID_CDCACM, /* idProduct */            // idProduct: 0x0fe1
    0x0101, /* bcdDevice */                    // 1.1
    0x01, /* iManufacturer */                  // Manufacturer
    0x02, /* iProduct */                       // Product
    0x03, /* iSerialNumber */                  // Serial Number
    0x01                                       /* bNumConfigurations */
};

/**
 @name config_descriptor_cdcacm
 @brief Configuration descriptor for Run Time mode.
 */
//@{
struct PACK config_descriptor_cdcacm
{
  USB_configuration_descriptor configuration;
  USB_interface_association_descriptor interface_association;
  USB_interface_descriptor interface_control;
  USB_CDC_ClassSpecificDescriptorHeaderFormat cdcCPDHF;
  USB_CDC_UnionInterfaceFunctionalDescriptor cdcUIFD;
  USB_CDC_CallManagementFunctionalDescriptor cdcCMFD;
  USB_CDC_AbstractControlManagementFunctionalDescriptor cdcACMFD;
  USB_endpoint_descriptor endpoint_control;
  USB_interface_descriptor interface_data;
  USB_endpoint_descriptor endpoint_data_out;
  USB_endpoint_descriptor endpoint_data_in;
  USB_interface_descriptor dfu_interface;
  USB_dfu_functional_descriptor dfu_functional;
};

// Fields marked with * are updated with information in device_config[]
DESCRIPTOR_QUALIFIER struct config_descriptor_cdcacm config_descriptor_cdcacm =
    {
        {
            sizeof(USB_configuration_descriptor),    /* configuration.bLength */
            USB_DESCRIPTOR_TYPE_CONFIGURATION,       /* configuration.bDescriptorType */
            sizeof(struct config_descriptor_cdcacm), /* configuration.wTotalLength */
            0x02,                                    /* configuration.bNumInterfaces */
            0x01,                                    /* configuration.bConfigurationValue */
            0x00,                                    /* configuration.iConfiguration */
            USB_CONFIG_BMATTRIBUTES_VALUE,           /* configuration.bmAttributes */
            0xFA /* configuration.bMaxPower */       // 500mA
        },

        {
            sizeof(USB_interface_association_descriptor), /* interface_association.bLength */
            USB_DESCRIPTOR_TYPE_INTERFACE_ASSOCIATION,    /* interface_association.bDescriptorType */
            0,                                            /* interface_association.bFirstInterface */
            2,                                            /* interface_association.bInterfaceCount */
            USB_CLASS_CDC_CONTROL,                        /* interface_association.bFunctionClass */
            USB_SUBCLASS_CDC_CONTROL_ABSTRACT,            /* interface_association.bFunctionSubClass */
            USB_PROTOCOL_CDC_CONTROL_ITU_T_V250,          /* interface_association.bFunctionProtocol */
            2 /* interface_association.iFunction */       // "FT900 CDCACM"
        },

        // ---- INTERFACE DESCRIPTOR for CDCACM Control ----
        {
            sizeof(USB_interface_descriptor),                                               /* interface_control.bLength */
            USB_DESCRIPTOR_TYPE_INTERFACE,                                                  /* interface_control.bDescriptorType */
            0,                                                                              /* interface_control.bInterfaceNumber */
            0x00,                                                                           /* interface_control.bAlternateSetting */
            0x01,                                                                           /* interface_control.bNumEndpoints */
            USB_CLASS_CDC_CONTROL, /* interface_control.bInterfaceClass */                  // CDC Class
            USB_SUBCLASS_CDC_CONTROL_ABSTRACT, /* interface_control.bInterfaceSubClass */   // Abstract Control Model
            USB_PROTOCOL_CDC_CONTROL_ITU_T_V250, /* interface_control.bInterfaceProtocol */ // No built-in protocol
            0x00 /* interface_control.iInterface */                                         // Unused
        },

        // ---- FUNCTIONAL DESCRIPTORS for CDCACM ----
        {
            sizeof(USB_CDC_ClassSpecificDescriptorHeaderFormat),     /* cdcCPDHF.bFunctionLength */
            USB_CDC_DESCRIPTOR_TYPE_CS_INTERFACE,                    /* cdcCPDHF.bDescriptorType */
            USB_CDC_DESCRIPTOR_SUBTYPE_HEADER_FUNCTIONAL_DESCRIPTOR, /* cdcCPDHF.bDescriptorSubtype */
            0x0110                                                   /* cdcCPDHF.bcdCDC */
        },

        {
            sizeof(USB_CDC_UnionInterfaceFunctionalDescriptor),     /* cdcUIFD.bFunctionLength */
            USB_CDC_DESCRIPTOR_TYPE_CS_INTERFACE,                   /* cdcUIFD.bDescriptorType */
            USB_CDC_DESCRIPTOR_SUBTYPE_UNION_FUNCTIONAL_DESCRIPTOR, /* cdcUIFD.bDescriptorSubtype */
            0,                                                      /* cdcUIFD.bControlInterface */
            1                                                       /* cdcUIFD.bSubordinateInterface0 */
        },

        {
            sizeof(USB_CDC_CallManagementFunctionalDescriptor),               /* cdcCMFD.bFunctionLength */
            USB_CDC_DESCRIPTOR_TYPE_CS_INTERFACE,                             /* cdcCMFD.bDescriptorType */
            USB_CDC_DESCRIPTOR_SUBTYPE_CALL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR, /* cdcCMFD.bDescriptorSubtype */
            USB_CDC_CM_CAPABILITIES_NONE,                                     /* cdcCMFD.bmCapabilities */
            0x01                                                              /* cdcCMFD.bDataInterface */
        },

        {
            sizeof(USB_CDC_AbstractControlManagementFunctionalDescriptor),                /* cdcACMFD.bFunctionLength */
            USB_CDC_DESCRIPTOR_TYPE_CS_INTERFACE,                                         /* cdcACMFD.bDescriptorType */
            USB_CDC_DESCRIPTOR_SUBTYPE_ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL_DESCRIPTOR, /* cdcACMFD.bDescriptorSubtype */
            USB_CDC_ACM_CAPABILITIES_LINE_STATE_CODING                                    /* cdcACMFD.bmCapabilities */
        },

        // ---- ENDPOINT DESCRIPTOR for CDCACM Control ----
        {
            sizeof(USB_endpoint_descriptor),                         /* endpoint_control.bLength */
            USB_DESCRIPTOR_TYPE_ENDPOINT,                            /* endpoint_control.bDescriptorType */
            USB_ENDPOINT_DESCRIPTOR_EPADDR_IN | CDC_EP_NOTIFICATION, /* endpoint_control.bEndpointAddress */
            USB_ENDPOINT_DESCRIPTOR_ATTR_INTERRUPT,                  /* endpoint_control.bmAttributes */
            CDC_NOTIFICATION_EP_SIZE,                                /* endpoint_control.wMaxPacketSize */
            0x0a                                                     /* endpoint_control.bInterval */
        },

        // ---- INTERFACE DESCRIPTOR for CDCACM Data ----
        {
            sizeof(USB_interface_descriptor),                              /* interface_data.bLength */
            USB_DESCRIPTOR_TYPE_INTERFACE,                                 /* interface_data.bDescriptorType */
            1,                                                             /* interface_data.bInterfaceNumber */
            0x00,                                                          /* interface_data.bAlternateSetting */
            0x02,                                                          /* interface_data.bNumEndpoints */
            USB_CLASS_CDC_DATA, /* interface_data.bInterfaceClass */       // CDC Data Class
            USB_SUBCLASS_CDC_DATA, /* interface_data.bInterfaceSubClass */ // Abstract Control Model
            USB_PROTOCOL_CDC_DATA, /* interface_data.bInterfaceProtocol */ // No built-in protocol
            0x00 /* interface_data.iInterface */                           // Unused
        },

        // ---- ENDPOINT DESCRIPTORS for CDCACM Data ----
        {
            sizeof(USB_endpoint_descriptor),                      /* endpoint_data_out.bLength */
            USB_DESCRIPTOR_TYPE_ENDPOINT,                         /* endpoint_data_out.bDescriptorType */
            USB_ENDPOINT_DESCRIPTOR_EPADDR_OUT | CDC_EP_DATA_OUT, /* endpoint_data_out.bEndpointAddress */
            USB_ENDPOINT_DESCRIPTOR_ATTR_BULK,                    /* endpoint_data_out.bmAttributes */
            CDC_DATA_EP_SIZE,                                     /* endpoint_data_out.wMaxPacketSize */
            0x0a                                                  /* endpoint_data_out.bInterval */
        },

        {
            sizeof(USB_endpoint_descriptor),                    /* endpoint_data_in.bLength */
            USB_DESCRIPTOR_TYPE_ENDPOINT,                       /* endpoint_data_in.bDescriptorType */
            USB_ENDPOINT_DESCRIPTOR_EPADDR_IN | CDC_EP_DATA_IN, /* endpoint_data_in.bEndpointAddress */
            USB_ENDPOINT_DESCRIPTOR_ATTR_BULK,                  /* endpoint_data_in.bmAttributes */
            CDC_DATA_EP_SIZE,                                   /* endpoint_data_in.wMaxPacketSize */
            0x0a                                                /* endpoint_data_in.bInterval */
        },
};
//@}

/**
 @name USBD_cdc_line_coding
 @brief UART characteristics set by CDC ACM driver on host.
 */
static USB_CDC_line_coding cdc_line_coding = {
    19200,               /* dwDTERate */
    USB_CDC_STOP_BITS_1, /* bCharFormat */
    USB_CDC_PARITY_NONE, /* bParityType */
    USB_CDC_DATA_BITS_8, /* bDataBits */
};

/* END CDC Configuration */

volatile static uint32_t Head;
volatile static uint32_t Tail;

#define BUFF_SIZE (uint32_t)(2 * 2048u)
#define BUFF_MOD (BUFF_SIZE - 1)
#define Z_IsBuffFull() ((((Head + 1) & BUFF_MOD) == (Tail & BUFF_MOD)) ? (true) : (false))
#define Z_IsBuffEmpty() ((Head == Tail) ? (true) : (false))
#define Z_NumElem() ((Head - Tail) & BUFF_MOD)
uint8_t cdc_tx_buffer[BUFF_SIZE];

void usbdbg_write_byte(uint8_t b)
{
  if (!Z_IsBuffFull())
    cdc_tx_buffer[Head++ & BUFF_MOD] = b;
}

void powermanagement_ISR(void)
{
  if (SYS->PMCFG_H & MASK_SYS_PMCFG_DEV_CONN_DEV)
  {
    // Clear connection interrupt
    SYS->PMCFG_H = MASK_SYS_PMCFG_DEV_CONN_DEV;
    USBD_attach();
  }

  if (SYS->PMCFG_H & MASK_SYS_PMCFG_DEV_DIS_DEV)
  {
    // Clear disconnection interrupt
    SYS->PMCFG_H = MASK_SYS_PMCFG_DEV_DIS_DEV;
    USBD_detach();
  }

  if (SYS->PMCFG_H & MASK_SYS_PMCFG_HOST_RST_DEV)
  {
    // Clear Host Reset interrupt
    SYS->PMCFG_H = MASK_SYS_PMCFG_HOST_RST_DEV;
    USBD_resume();
  }

  if (SYS->PMCFG_H & MASK_SYS_PMCFG_HOST_RESUME_DEV)
  {
    // Clear Host Resume interrupt
    SYS->PMCFG_H = MASK_SYS_PMCFG_HOST_RESUME_DEV;
    if (!(SYS->MSC0CFG & MASK_SYS_MSC0CFG_DEV_RMWAKEUP))
    {
      // If we are driving K-state on Device USB port;
      // We must maintain the 1ms requirement before resuming the phy
      USBD_resume();
    }
  }
}

void ISR_timer(void)
{
  if (timer_is_interrupted(timer_select_a))
  {
    // Call USB timer handler to action transaction and hub timers.
    USBD_timer();
  }
}

/**
 @brief      USB class request handler
 @details    Handle class requests from the host application.
 The bRequest value is parsed and the appropriate
 action or function is performed. Additional values
 from the USB_device_request structure are decoded
 and the DFU state machine and status updated as
 required.
 @param[in]	req - USB_device_request structure containing the
 SETUP portion of the request from the host.
 @return		status - USBD_OK if successful or USBD_ERR_*
 if there is an error or the bRequest is not
 supported.
 **/

int8_t class_req_cb(USB_device_request *req)
{
  int8_t status = USBD_ERR_NOT_SUPPORTED;
  // uint8_t interface = LSB(req->wIndex) & 0x0F;
  uint8_t command[USB_CONTROL_EP_MAX_PACKET_SIZE];
  uint8_t request = req->bRequest;

  // For DFU requests the SETUP packet must be addressed to the
  // the DFU interface on the device.

  // For DFU requests ensure the recipient is an interface...
  if ((req->bmRequestType & USB_BMREQUESTTYPE_RECIPIENT_MASK) ==
      USB_BMREQUESTTYPE_RECIPIENT_INTERFACE)
  {
    switch (request)
    {
    case USB_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND:
      // Read and ignore encapsulated command.
      USBD_transfer_ep0(USBD_DIR_OUT, command,
                        USB_CONTROL_EP_MAX_PACKET_SIZE, req->wLength);
      // ACK
      USBD_transfer_ep0(USBD_DIR_IN, NULL, 0, 0);
      break;
    case USB_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE:
    case USB_CDC_REQUEST_SET_COMM_FEATURE:
    case USB_CDC_REQUEST_GET_COMM_FEATURE:
    case USB_CDC_REQUEST_CLEAR_COMM_FEATURE:
      break;

    case USB_CDC_REQUEST_SET_LINE_CODING:
      USBD_transfer_ep0(USBD_DIR_OUT, (uint8_t *)&cdc_line_coding,
                        sizeof(USB_CDC_line_coding), req->wLength);
      // ACK
      USBD_transfer_ep0(USBD_DIR_IN, NULL, 0, 0);
      // Update UART settings
      //			DPRINTF_INFO("set baud %ld, par %d, stop %d, data %d\r\n",
      //					cdc_line_coding.dwDTERate, cdc_line_coding.bParityType,
      //					cdc_line_coding.bCharFormat, cdc_line_coding.bDataBits);
      // uartCoding();
      // DPRINTF_INFO("PMSIZ = %08X, %08X", &__PMSIZE, __PMSIZE);
      status = USBD_OK;
      break;

    case USB_CDC_REQUEST_GET_LINE_CODING:
      USBD_transfer_ep0(USBD_DIR_IN, (uint8_t *)&cdc_line_coding,
                        sizeof(USB_CDC_line_coding), req->wLength);
      // ACK
      USBD_transfer_ep0(USBD_DIR_OUT, NULL, 0, 0);
      status = USBD_OK;
      //			DPRINTF_INFO("get baud %ld, par %d, stop %d, data %d\r\n",
      //					cdc_line_coding.dwDTERate, cdc_line_coding.bParityType,
      //					cdc_line_coding.bCharFormat, cdc_line_coding.bDataBits);
      break;

    case USB_CDC_REQUEST_SET_CONTROL_LINE_STATE:
      // Ignore the control line state
      // ACK
      USBD_transfer_ep0(USBD_DIR_IN, NULL, 0, 0);
      status = USBD_OK;
      break;

    case USB_CDC_REQUEST_SEND_BREAK:
      // USBD_transfer_ep0(USBD_DIR_IN, NULL, 0, 0);
      break;
    }
  }

  return status;
}

/**
 @brief      USB standard request handler for GET_DESCRIPTOR
 @details    Handle standard GET_DESCRIPTOR requests from the host
 application.
 The hValue is parsed and the appropriate device,
 configuration or string descriptor is selected.
 For device and configuration descriptors the DFU
 state machine determines which descriptor to use.
 For string descriptors the lValue selects which
 string from the string_descriptors table to use.
 The string table is automatically traversed to find
 the correct string and the length is taken from the
 string descriptor.
 @param[in]	req - USB_device_request structure containing the
 SETUP portion of the request from the host.
 @return		status - USBD_OK if successful or USBD_ERR_*
 if there is an error or the bmRequestType is not
 supported.
 **/
int8_t standard_req_get_descriptor(USB_device_request *req, uint8_t **buffer,
                                   uint16_t *len)
{
  uint8_t *src = NULL;
  uint16_t length = req->wLength;
  uint8_t hValue = req->wValue >> 8;
  uint8_t lValue = req->wValue & 0x00ff;
  uint8_t i;
  uint8_t slen;

  switch (hValue)
  {
  case USB_DESCRIPTOR_TYPE_DEVICE:
    src = (uint8_t *)&device_descriptor_cdcacm;

    if (length > sizeof(USB_device_descriptor)) // too many bytes requested
      length = sizeof(USB_device_descriptor);   // Entire structure.
    break;

  case USB_DESCRIPTOR_TYPE_CONFIGURATION:
    src = (uint8_t *)&config_descriptor_cdcacm;
    if (length > sizeof(config_descriptor_cdcacm)) // too many bytes requested
      length = sizeof(config_descriptor_cdcacm);   // Entire structure.

    break;

  case USB_DESCRIPTOR_TYPE_STRING:
    // Find the nth string in the string descriptor table
    i = 0;
    while ((slen = string_descriptor[i]) > 0)
    {
      // Point to start of string descriptor in __code segment
      // Typecast prevents warning for losing const when USBD_transfer
      // is called
      src = (uint8_t *)&string_descriptor[i];
      if (lValue == 0)
      {
        break;
      }
      i += slen;
      lValue--;
    }
    if (lValue > 0)
    {
      // String not found
      return USBD_ERR_NOT_SUPPORTED;
    }
    // Update the length returned only if it is less than the requested
    // size
    if (length > slen)
    {
      length = slen;
    }

    break;

  default:
    return USBD_ERR_NOT_SUPPORTED;
  }

  *buffer = src;
  *len = length;

  return USBD_OK;
}

/**
 @brief      USB vendor request handler
 @details    Handle vendor requests from the host application.
 The bRequest value is parsed and the appropriate
 action or function is performed. Additional values
 from the USB_device_request structure are decoded
 and provided to other handlers.
 There are no vendor requests requiring handling in
 this firmware.
 @param[in]	req - USB_device_request structure containing the
 SETUP portion of the request from the host.
 @return		status - USBD_OK if successful or USBD_ERR_*
 if there is an error or the bRequest is not
 supported.
 **/
int8_t vendor_req_cb(USB_device_request *req)
{
  int8_t status = USBD_ERR_NOT_SUPPORTED;
  (void)req;

  return status;
}

/**
 @brief      USB suspend callback
 @details    Called when the USB bus enters the suspend state.
 @param[in]	status - unused.
 @return		N/A
 **/
void suspend_cb(uint8_t status)
{
  (void)status;
  return;
}

/**
 @brief      USB resume callback
 @details    Called when the USB bus enters the resume state
 prior to restating after a suspend.
 @param[in]  status - unused.
 @return     N/S
 **/
void resume_cb(uint8_t status)
{
  (void)status;
  return;
}

/**
 @brief      USB reset callback
 @details    Called when the USB bus enters the reset state.
 @param[in]	status - unused.
 @return		N/A
 **/
void reset_cb(uint8_t status)
{
  (void)status;

  USBD_set_state(USBD_STATE_DEFAULT);

  return;
}

/* For debugging endpoint transactions. */
void ep_cb(USBD_ENDPOINT_NUMBER ep_number)
{
  DPRINTF_INFO("EP%d\r\n", ep_number);
}

void cdc_send_serial_state_notification()
{
  struct
  { // Note: structure must be packed
    USB_CDC_Notification header;
    union
    {
      uint16_t buffer;
      USB_CDC_UartStateBitmap serialState;
    };
  } notification;

  notification.header.bmRequestType = USB_BMREQUESTTYPE_DIR_DEV_TO_HOST |
                                      USB_BMREQUESTTYPE_CLASS |
                                      USB_BMREQUESTTYPE_RECIPIENT_INTERFACE;
  notification.header.bNotification = USB_CDC_NOTIFICAITON_SERIAL_STATE;
  notification.header.wValue = 0;
  notification.header.wIndex = 0; // CDC ACM interface
  notification.header.wLength = 2;
  notification.buffer = 0;
  // All Serial State bits are set to zero (disabled).
  notification.serialState.bRxCarrier = 0;
  notification.serialState.bTxCarrier = 0;

  USBD_transfer(CDC_EP_NOTIFICATION, (uint8_t *)&notification,
                sizeof(notification));
}

void usbdbg_init(void)
{
  int8_t status;
#if 0
  // This timer is *not* required for normal USB operation, it's only used for advanced use-cases
  // like suspend-resume etc, so it's safe to disable it for our logging use-case.
#if defined(__FT900__)
  timer_prescaler(1000);
#elif defined(__FT930__)
  timer_prescaler(timer_select_a, 1000);
#endif
  timer_init(timer_select_a, 100, timer_direction_down,
             timer_prescaler_select_on, timer_mode_continuous);
  timer_enable_interrupt(timer_select_a);
  timer_start(timer_select_a);

  interrupt_attach(interrupt_timers, (int8_t)interrupt_timers, ISR_timer);
#endif
  interrupt_attach(interrupt_0, (int8_t)interrupt_0, powermanagement_ISR);
  interrupt_enable_globally();

  USBD_ctx usb_ctx;

  memset(&usb_ctx, 0, sizeof(usb_ctx));

  usb_ctx.standard_req_cb = NULL;
  usb_ctx.get_descriptor_cb = standard_req_get_descriptor;
  usb_ctx.class_req_cb = class_req_cb;
  usb_ctx.vendor_req_cb = vendor_req_cb;
  usb_ctx.suspend_cb = suspend_cb;
  usb_ctx.resume_cb = resume_cb;
  usb_ctx.reset_cb = reset_cb;
  usb_ctx.lpm_cb = NULL;
  usb_ctx.speed = USBD_SPEED_HIGH;

  // Initialise the USB device with a control endpoint size
  // of 8 to 64 bytes. This must match the size for bMaxPacketSize0
  // defined in the device descriptor.
  usb_ctx.ep0_size = USB_CONTROL_EP_SIZE;
  // usb_ctx.ep0_cb = ep_cb;

  USBD_initialise(&usb_ctx);

  for (;;)
  {
    if (!USBD_is_connected())
    {
      continue;
    }
    /* Get USB speed */
    USBD_attach();
    if (USBD_connect() == USBD_OK)
    {
      if (USBD_DFU_is_runtime())
      {
        // Start the emulation code.

        USBD_create_endpoint(CDC_EP_NOTIFICATION, USBD_EP_INT, USBD_DIR_IN,
                             CDC_NOTIFICATION_USBD_EP_SIZE, USBD_DB_OFF, NULL /*ep_cb*/);
        USBD_create_endpoint(CDC_EP_DATA_OUT, USBD_EP_BULK, USBD_DIR_OUT,
                             CDC_DATA_USBD_EP_SIZE, USBD_DB_ON, NULL /*ep_cb*/);
        USBD_create_endpoint(CDC_EP_DATA_IN, USBD_EP_BULK, USBD_DIR_IN,
                             CDC_DATA_USBD_EP_SIZE, USBD_DB_ON, NULL /*ep_cb*/);

        cdc_send_serial_state_notification();
        break;
      }
      else
      {
        // In DFU mode. Process USB requests.
        do
        {
          status = (USBD_get_state() < USBD_STATE_DEFAULT) ? USBD_ERR_NOT_CONFIGURED : USBD_OK;
        } while (status == USBD_OK);
      }
      USBD_detach();
      DPRINTF_INFO("Restarting\r\n");
    }
  }
}

void send_over_usb(uint8_t *p, uint32_t len)
{
  uint32_t sent = len;
  while (sent)
  {
    sent -= USBD_transfer(CDC_EP_DATA_IN, p, sent);
  }
}

void usbdbg_main(void)
{
  int8_t status;

  do
  {

    while (!USBD_ep_buffer_full(CDC_EP_DATA_IN) && !Z_IsBuffEmpty())
    {
      // Read in a packet of data from the UART.
      // (up to the size of the ring buffer)
      uint32_t len = Z_NumElem();
      if ((Tail & BUFF_MOD) + len <= BUFF_SIZE)
      { // no rollover?
        send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], len);
        Tail += len;
      }
      else
      {
        // This assumes that all the data will get transferred in USBD_transfer(), otherwise you need a loop
        len -= BUFF_SIZE - (Tail & BUFF_MOD);
        send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], BUFF_SIZE - (Tail & BUFF_MOD));
        Tail += BUFF_SIZE - (Tail & BUFF_MOD);
        send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], len);
        Tail += len;
      }
    }

    // If data is available on the USB OUT endpoint and there is space
    // in the ring buffer to receive it then read it in from the host.
    if ((USBD_ep_buffer_full(CDC_EP_DATA_OUT)))
    { //&& (uart0BufferOut_avail >= CDC_DATA_EP_SIZE)
      uint8_t bufUsb2Uart[CDC_DATA_EP_SIZE] = {0};
      // Read in a packet of data from the CDC DATA interface.
      USBD_transfer(CDC_EP_DATA_OUT, (uint8_t *)&bufUsb2Uart, CDC_DATA_EP_SIZE);
    }
    status = (USBD_get_state() < USBD_STATE_DEFAULT) ? USBD_ERR_NOT_CONFIGURED : USBD_OK;
    (void)status;
  } while (0);
}

void usbdbg_try_to_send(void)
{
  int8_t status;

  while (!USBD_ep_buffer_full(CDC_EP_DATA_IN) && !Z_IsBuffEmpty())
  {
    // Read in a packet of data from the UART.
    // (up to the size of the ring buffer)
    uint32_t len = Z_NumElem();
    if ((Tail & BUFF_MOD) + len <= BUFF_SIZE)
    { // no rollover?
      send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], len);
      Tail += len;
    }
    else
    {
      // This assumes that all the data will get transferred in USBD_transfer(), otherwise you need a loop
      len -= BUFF_SIZE - (Tail & BUFF_MOD);
      send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], BUFF_SIZE - (Tail & BUFF_MOD));
      Tail += BUFF_SIZE - (Tail & BUFF_MOD);
      send_over_usb(&cdc_tx_buffer[Tail & BUFF_MOD], len);
      Tail += len;
    }
  }

  // If data is available on the USB OUT endpoint and there is space
  // in the ring buffer to receive it then read it in from the host.
  if ((USBD_ep_buffer_full(CDC_EP_DATA_OUT)))
  { //&& (uart0BufferOut_avail >= CDC_DATA_EP_SIZE)
    uint8_t bufUsb2Uart[CDC_DATA_EP_SIZE] = {0};
    // Read in a packet of data from the CDC DATA interface.
    USBD_transfer(CDC_EP_DATA_OUT, (uint8_t *)&bufUsb2Uart, CDC_DATA_EP_SIZE);
  }
  status = (USBD_get_state() < USBD_STATE_DEFAULT) ? USBD_ERR_NOT_CONFIGURED : USBD_OK;
  (void)status;
}

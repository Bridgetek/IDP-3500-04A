/*
 * @file usbdbg.h
 *
 *  Created on: Jun 20, 2017
 *      Author: govind.mukundan
 */

#ifndef INCLUDES_USBDBG_H_
#define INCLUDES_USBDBG_H_

/* USB CDC Stuff */

/* For MikroC const qualifier will place variables in Flash
 * not just make them constant.
 */
#if defined(__GNUC__)
#define DESCRIPTOR_QUALIFIER const
#elif defined(__MIKROC_PRO_FOR_FT90x__)
#define DESCRIPTOR_QUALIFIER data
#endif

/* CONSTANTS ***********************************************************************/

/**
 @name USB and Hub Configuration
 @brief Indication of how the USB device is powered and the size of
   the control endpoint Max Packets.
 */
//@{
// USB Bus Powered - set to 1 for self-powered or 0 for bus-powered
#ifndef USB_SELF_POWERED
#define USB_SELF_POWERED 0
#endif // USB_SELF_POWERED
#if USB_SELF_POWERED == 1
#define USB_CONFIG_BMATTRIBUTES_VALUE (USB_CONFIG_BMATTRIBUTES_SELF_POWERED | USB_CONFIG_BMATTRIBUTES_RESERVED_SET_TO_1)
#else // USB_SELF_POWERED
#define USB_CONFIG_BMATTRIBUTES_VALUE USB_CONFIG_BMATTRIBUTES_RESERVED_SET_TO_1
#endif // USB_SELF_POWERED
// USB Endpoint Zero packet size (both must match)
#define USB_CONTROL_EP_MAX_PACKET_SIZE 64
#define USB_CONTROL_EP_SIZE USBD_EP_SIZE_64
//@}

/**
 @name DFU Configuration
 @brief Determines the parts of the DFU specification which are supported
        by the DFU library code. Features can be disabled if required.
 */
//@{
#define DFU_ATTRIBUTES USBD_DFU_ATTRIBUTES
//@}

/**
 @name Device Configuration Areas
 @brief Size and location reserved for string descriptors.
 Leaving the allocation size blank will make an array exactly the size
 of the string allocation.
 Note: Specifying the location is not supported by the GCC compiler.
 */
//@{
// String descriptors - allow a maximum of 256 bytes for this
#define STRING_DESCRIPTOR_LOCATION 0x80
#define STRING_DESCRIPTOR_ALLOCATION 0x100
//@}

/**
 @name DFU_TRANSFER_SIZE definition.
 @brief Number of bytes in block, sent in each DFU_DNLOAD request
 from the DFU update program on the host. This is simplified
 in that the meaning of a block is an arbitrary number of
 bytes. This is intentionally a multiple of the maximum
 packet size for the control endpoints.
 It is used in the DFU functional descriptor as wTransferSize.
 The maximum size supported by the DFU library is 256 bytes
 which is the size of a page of Flash.
 */
//@{
#define DFU_TRANSFER_SIZE USBD_DFU_MAX_BLOCK_SIZE
#define DFU_TIMEOUT USBD_DFU_TIMEOUT
//@}

/**
 @name USB_PID_CDCACM configuration.
 @brief Run Time Product ID for CDC function.
 */
//@{
#define USB_PID_CDCACM 0x0fd1
//@}

/**
 @name DFU_USB_INTERFACE configuration..
 @brief Run Time and DFU Mode Interface Numbers.
 */
//@{
#define DFU_USB_INTERFACE_RUNTIME 2
#define DFU_USB_INTERFACE_DFUMODE 0
//@}

/**
   @name Disable DFU function
   @brief Disable the DFU interface in this application.
       Normally enabled.
*/
#define DISABLE_DFU

/**
 @name WCID_VENDOR_REQUEST_CODE for WCID.
 @brief Unique vendor request code for WCID OS Vendor Extension validation.
*/
//@{
#define WCID_VENDOR_REQUEST_CODE 0x4A /*same WCID code as that of B-DFU */
//@}

/**
    @name Microsoft WCID Information
    @brief Definitions for WCID String Descriptors and vendor requests.
 **/
//@{
#define USB_MICROSOFT_WCID_VERSION 0x0100

#define USB_MICROSOFT_WCID_STRING_DESCRIPTOR 0xEE
#define USB_MICROSOFT_WCID_STRING_LENGTH 0x12
#define USB_MICROSOFT_WCID_STRING_SIGNATURE 'M', 0x00, 'S', 0x00, \
                                            'F', 0x00, 'T', 0x00, '1', 0x00, '0', 0x00, '0', 0x00,

#define USB_MICROSOFT_WCID_STRING(A) \
  USB_MICROSOFT_WCID_STRING_LENGTH,  \
      USB_DESCRIPTOR_TYPE_STRING, USB_MICROSOFT_WCID_STRING_SIGNATURE A, 0x00,

#define USB_MICROSOFT_WCID_FEATURE_WINDEX_COMPAT_ID 0x0004
//@}

/**
 @brief Endpoint definitions for CDCACM.
 */
//@{
#define CDC_EP_NOTIFICATION USBD_EP_1
#define CDC_EP_DATA_IN USBD_EP_2
#define CDC_EP_DATA_OUT USBD_EP_3
#define CDC_NOTIFICATION_EP_SIZE 0x10
#define CDC_NOTIFICATION_USBD_EP_SIZE USBD_EP_SIZE_16
#define CDC_DATA_EP_SIZE 512
#define CDC_DATA_USBD_EP_SIZE USBD_EP_SIZE_512
//@}

#ifdef DEBUG
  #define DPRINTF_INFO(str, ...) printf((s), __VA_ARGS__)
#else
  #define DPRINTF_INFO(str, ...)
#endif

void usbdbg_init(void);
void usbdbg_main(void);
void usbdbg_write_byte(uint8_t b);
void usbdbg_try_to_send(void);

#endif /* INCLUDES_USBDBG_H_ */

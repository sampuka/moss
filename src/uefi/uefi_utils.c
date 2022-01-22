#include "uefi_utils.h"

uint16_t* uefi_utils_status_string(EFI_STATUS status)
{
    switch (status)
    {
        case EFI_SUCCESS: return u"EFI_SUCCESS";
        case EFI_LOAD_ERROR: return u"EFI_LOAD_ERROR";
        case EFI_INVALID_PARAMETER: return u"EFI_INVALID_PARAMETER";
        case EFI_UNSUPPORTED: return u"EFI_UNSUPPORTED";
        case EFI_BAD_BUFFER_SIZE: return u"EFI_BAD_BUFFER_SIZE";
        case EFI_BUFFER_TOO_SMALL: return u"EFI_BUFFER_TOO_SMALL";
        case EFI_NOT_READY: return u"EFI_NOT_READY";
        case EFI_DEVICE_ERROR: return u"EFI_DEVICE_ERROR";
        case EFI_WRITE_PROTECTED: return u"EFI_WRITE_PROTECTED";
        case EFI_OUT_OF_RESOURCES: return u"EFI_OUT_OF_RESOURCES";
        case EFI_VOLUME_CORRUPTED: return u"EFI_VOLUME_CORRUPTED";
        case EFI_VOLUME_FULL: return u"EFI_VOLUME_FULL";
        case EFI_NO_MEDIA: return u"EFI_NO_MEDIA";
        case EFI_MEDIA_CHANGED: return u"EFI_MEDIA_CHANGED";
        case EFI_NOT_FOUND: return u"EFI_NOT_FOUND";
        case EFI_ACCESS_DENIED: return u"EFI_ACCESS_DENIED";
        case EFI_NO_RESPONSE: return u"EFI_NO_RESPONSE";
        case EFI_NO_MAPPING: return u"EFI_NO_MAPPING";
        case EFI_TIMEOUT: return u"EFI_TIMEOUT";
        case EFI_NOT_STARTED: return u"EFI_NOT_STARTED";
        case EFI_ALREADY_STARTED: return u"EFI_ALREADY_STARTED";
        case EFI_ABORTED: return u"EFI_ABORTED";
        case EFI_ICMP_ERROR: return u"EFI_ICMP_ERROR";
        case EFI_TFTP_ERROR: return u"EFI_TFTP_ERROR";
        case EFI_PROTOCOL_ERROR: return u"EFI_PROTOCOL_ERROR";
        case EFI_INCOMPATIBLE_VERSION: return u"EFI_INCOMPATIBLE_VERSION";
        case EFI_SECURITY_VIOLATION: return u"EFI_SECURITY_VIOLATION";
        case EFI_CRC_ERROR: return u"EFI_CRC_ERROR";
        case EFI_END_OF_MEDIA: return u"EFI_END_OF_MEDIA";
        case EFI_END_OF_FILE: return u"EFI_END_OF_FILE";
        case EFI_INVALID_LANGUAGE: return u"EFI_INVALID_LANGUAGE";
        case EFI_COMPROMISED_DATA: return u"EFI_COMPROMISED_DATA";
        //case EFI_HTTP_ERROR: return u"EFI_HTTP_ERROR";
        case EFI_WARN_UNKNOWN_GLYPH: return u"EFI_WARN_UNKNOWN_GLYPH";
        case EFI_WARN_DELETE_FAILURE: return u"EFI_WARN_DELETE_FAILURE";
        case EFI_WARN_WRITE_FAILURE: return u"EFI_WARN_WRITE_FAILURE";
        case EFI_WARN_BUFFER_TOO_SMALL: return u"EFI_WARN_BUFFER_TOO_SMALL";
        //case EFI_WARN_STALE_DATA: return u"EFI_WARN_STALE_DATA";
        //case EFI_WARN_FILE_SYSTEM: return u"EFI_WARN_FILE_SYSTEM";
        default: return u"UKNOWN EFI STATUS!";
    }
}

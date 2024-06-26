// Copyright 2022 Samsung Electronics Co., Ltd. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_PLUGIN_DRM_MANAGER_PROXY_H_
#define FLUTTER_PLUGIN_DRM_MANAGER_PROXY_H_

typedef enum {
  DM_ERROR_NONE = 0,                /**< Success */
  DM_ERROR_INVALID_PARAM,           /**< Invalid parameter */
  DM_ERROR_INVALID_OPERATE,         /**< Invalid operation */
  DM_ERROR_INVALID_HANDLE,          /**< Invalid handle */
  DM_ERROR_INTERNAL_ERROR,          /**< Internal error */
  DM_ERROR_TIMEOUT,                 /**< Timeout */
  DM_ERROR_MANIFEST_DOWNLOAD_ERROR, /**< Manifest download error */
  DM_ERROR_MANIFEST_PARSE_ERROR,    /**< Manifest parse error */
  DM_ERROR_FIND_NOPSSHDATA,         /**< No pssh data */

  DM_ERROR_MALLOC = 10, /**< Malloc error */
  DM_ERROR_DL,          /**< Load so error */

  DM_ERROR_INVALID_URL = 20,       /**< Invalid url */
  DM_ERROR_INVALID_SESSION,        /**< Invalid session */
  DM_ERROR_UNSUPPORTED_URL_SUFFIX, /**< Unsupported url suffix */
  DM_ERROR_INITIALIZE_FAILED,      /**< Failed to initialize DRM */

  DM_ERROR_DASH_INIT = 30, /**< DASH init failed */
  DM_ERROR_DASH_CLOSE,     /**< DASH close failed */
  DM_ERROR_DASH_OPEN,      /**< DASH open failed */

  DM_ERROR_DRM_WEB_SET = 40, /**< DRM web set failed */

  DM_ERROR_PR_HANDLE_CREATE = 50, /**< Playready handle create failed */
  DM_ERROR_PR_OPEN,               /**< Playready open failed */
  DM_ERROR_PR_DESTROY,            /**< Playready destroy failed */
  DM_ERROR_PR_GENCHALLENGE,       /**< Playready genchallenge failed */
  DM_ERROR_PR_INSTALL_LICENSE,    /**< Playready install license failed */
  DM_ERROR_PR_GETRIGHTS,          /**< Playready get rights failed */
  DM_ERROR_PR_STATUS,             /**< Playready get status failed */

  DM_ERROR_VMX_HANDLE_CREATE = 60, /**< Verimatrix handle create failed */
  DM_ERROR_VMX_FINALIZE,           /**< Verimatrix finalize failed */
  DM_ERROR_VMX_GET_UNIQUE_ID,      /**< Verimatrix get unique ID failed */

  DM_ERROR_MARLIN_OPEN = 70,   /**< Marlin open failed */
  DM_ERROR_MARLIN_CLOSE,       /**< Marlin close failed */
  DM_ERROR_MARLIN_GET_RIGHTS,  /**< Marlin get rights failed */
  DM_ERROR_MARLIN_GET_LICENSE, /**< Marlin get license failed */

  DM_ERROR_WVCDM_HANDLE_CREATE = 80,  /**< Widevinecdm handle create failed */
  DM_ERROR_WVCDM_DESTROY,             /**< Widevinecdm destroy failed */
  DM_ERROR_WVCDM_OPEN_SESSION,        /**< Widevinecdm open failed */
  DM_ERROR_WVCDM_CLOSE_SESSION,       /**< Widevinecdm close failed */
  DM_ERROR_WVCDM_GET_PROVISION,       /**< Widevinecdm get provision failed */
  DM_ERROR_WVCDM_GENERATE_KEYREQUEST, /**< Widevinecdm generate key request
                                         failed */
  DM_ERROR_WVCDM_ADD_KEY,             /**< Widevinecdm add key failed */
  DM_ERROR_WVCDM_REGISTER_EVENT,      /**< Widevinecdm register event failed */

  DM_ERROR_EME_SESSION_HANDLE_CREATE = 90, /**< EME handle create failed */
  DM_ERROR_EME_SESSION_CREATE,             /**< EME session create failed */
  DM_ERROR_EME_SESSION_DESTROY,            /**< EME session destroy failed */
  DM_ERROR_EME_SESSION_UPDATE,             /**< EME session update failed */
  DM_ERROR_EME_SESSION_REQUEST,            /**< EME session request failed */
  DM_ERROR_EME_WEB_OPERATION,              /**< EME web operation failed */
  DM_ERROR_EME_TYPE_NOT_SUPPORTED,         /**< EME type not supported */
  //...
  DM_ERROR_UNKOWN,
} dm_error_e;

typedef enum {
  DM_TYPE_NONE = 0,             /**< None */
  DM_TYPE_PLAYREADY = 1,        /**< Playready */
  DM_TYPE_MARLINMS3 = 2,        /**< Marlinms3 */
  DM_TYPE_VERIMATRIX = 3,       /**< Verimatrix */
  DM_TYPE_WIDEVINE_CLASSIC = 4, /**< Widevine classic */
  DM_TYPE_SECUREMEDIA = 5,      /**< Securemedia */
  DM_TYPE_SDRM = 6,             /**< SDRM */
  DM_TYPE_VUDU = 7,             /**< Vudu */
  DM_TYPE_WIDEVINE = 8,         /**< Widevine cdm */
  DM_TYPE_LYNK = 9,             /**< Lynk */
  DM_TYPE_CLEARKEY = 13,        /**< Clearkey */
  DM_TYPE_EME = 14,             /**< EME */
  //...
  DM_TYPE_MAX,
} dm_type_e;

typedef struct SetDataParam_s {
  void* param1; /**< Parameter 1 */
  void* param2; /**< Parameter 2 */
  void* param3; /**< Parameter 3 */
  void* param4; /**< Parameter 4 */
} SetDataParam_t;

typedef void* DRMSessionHandle_t;

typedef int (*FuncDMGRSetData)(DRMSessionHandle_t drm_session,
                               const char* data_type, void* input_data);
typedef int (*FuncDMGRGetData)(DRMSessionHandle_t drm_session,
                               const char* data_type, void* output_data);
typedef void (*FuncDMGRSetDRMLocalMode)();
typedef DRMSessionHandle_t (*FuncDMGRCreateDRMSession)(
    dm_type_e type, const char* drm_sub_type);
typedef bool (*FuncDMGRSecurityInitCompleteCB)(int* drm_handle,
                                               unsigned int len,
                                               unsigned char* pssh_data,
                                               void* user_data);
typedef int (*FuncDMGRReleaseDRMSession)(DRMSessionHandle_t drm_session);

class DrmManagerProxy {
 public:
  static DrmManagerProxy& GetInstance() {
    static DrmManagerProxy instance;
    return instance;
  }
  DrmManagerProxy(const DrmManagerProxy&) = delete;
  DrmManagerProxy(const DrmManagerProxy&&) = delete;
  DrmManagerProxy& operator=(const DrmManagerProxy&) = delete;

  int DMGRSetData(DRMSessionHandle_t drm_session, const char* data_type,
                  void* input_data);
  int DMGRGetData(DRMSessionHandle_t drm_session, const char* data_type,
                  void* output_data);
  void DMGRSetDRMLocalMode();
  DRMSessionHandle_t DMGRCreateDRMSession(dm_type_e type,
                                          const char* drm_sub_type);
  bool DMGRSecurityInitCompleteCB(int* drm_handle, unsigned int len,
                                  unsigned char* pssh_data, void* user_data);
  int DMGRReleaseDRMSession(DRMSessionHandle_t drm_session);

 private:
  DrmManagerProxy();
  ~DrmManagerProxy();
  bool Initialize();
  void* drm_manager_handle_ = nullptr;
  FuncDMGRSetData dmgr_set_data_ = nullptr;
  FuncDMGRGetData dmgr_get_data_ = nullptr;
  FuncDMGRSetDRMLocalMode dmgr_set_drm_local_mode_ = nullptr;
  FuncDMGRCreateDRMSession dmgr_create_drm_session_ = nullptr;
  FuncDMGRSecurityInitCompleteCB dmgr_security_init_complete_cb_ = nullptr;
  FuncDMGRReleaseDRMSession dmgr_release_drm_session_ = nullptr;
  bool is_valid_ = false;
};

#endif  // FLUTTER_PLUGIN_DRM_MANAGER_PROXY_H_

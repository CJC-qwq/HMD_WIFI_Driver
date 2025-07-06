#pragma once

#include <variant>
#include <openvr_driver.h>
#include <Driver/DeviceType.hpp>

namespace ExampleDriver {

    class IVRDevice : public vr::ITrackedDeviceServerDriver {
    public:
        /// <summary>
        /// 返回该设备的序列号字符串
        /// </summary>
        /// <returns>设备序列号</returns>
        virtual std::string GetSerial() = 0;

        /// <summary>
        /// 运行该设备的更新逻辑。
        /// 每帧调用一次
        /// </summary>
        virtual void Update() = 0;

        /// <summary>
        /// 返回OpenVR设备索引
        /// 对于HMD应为0
        /// </summary>
        /// <returns>OpenVR设备索引</returns>
        virtual vr::TrackedDeviceIndex_t GetDeviceIndex() = 0;
        
        /// <summary>
        /// 返回该设备的类型
        /// </summary>
        /// <returns>设备类型</returns>
        virtual DeviceType GetDeviceType() = 0;
        
        /// <summary>
        /// 生成一个默认的设备姿态
        /// </summary>
        /// <returns>默认初始化的姿态</returns>
        static inline vr::DriverPose_t MakeDefaultPose(bool connected = true, bool tracking = true) {
            vr::DriverPose_t out_pose = { 0 };

            out_pose.deviceIsConnected = connected;
            out_pose.poseIsValid = tracking;
            out_pose.result = tracking ? vr::ETrackingResult::TrackingResult_Running_OK : vr::ETrackingResult::TrackingResult_Running_OutOfRange;
            out_pose.willDriftInYaw = false;
            out_pose.shouldApplyHeadModel = false;
            out_pose.qDriverFromHeadRotation.w = out_pose.qWorldFromDriverRotation.w = out_pose.qRotation.w = 1.0;

            return out_pose;
        }

        // 继承自 ITrackedDeviceServerDriver
        virtual vr::EVRInitError Activate(uint32_t unObjectId) = 0;
        virtual void Deactivate() = 0;
        virtual void EnterStandby() = 0;
        virtual void* GetComponent(const char* pchComponentNameAndVersion) = 0;
        virtual void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) = 0;
        virtual vr::DriverPose_t GetPose() = 0;

        ~IVRDevice() = default;
    };
};
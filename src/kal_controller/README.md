# KAL 控制器

🚗 认知汽车实验室(KAL)项目的先进车辆控制器实现

[![构建状态](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://gitlab.mrt.kit.edu/kognitive_automobile_labor/shared/kal_controller)
[![许可证](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/C%2B%2B-14%2B-blue.svg)](https://isocpp.org/)

## 📋 项目概述

KAL 控制器是一个复杂的车辆控制系统，结合了横向路径跟踪和纵向速度控制。它实现了增强版的纯追踪算法，具有自适应前瞻、预测控制和速度相关增益调度功能，确保平滑稳定的车辆控制。

### 核心特性

- 🎯 **自适应前瞻控制**: 基于车辆速度和路径曲率的动态前瞻距离
- 🔮 **预测控制**: 预测未来轨迹点以提升控制性能  
- ⚖️ **速度自适应增益**: 自动调整控制增益以防止高速时的振荡
- 🌊 **信号滤波**: 内置低通滤波器，确保更平滑的控制输出
- 📊 **调试接口**: 提供全面的调试信息用于分析和调优
- ✅ **鲁棒设计**: 包含异常处理和参数验证

## 🏗️ 系统架构

控制器围绕核心 `Controller` 类构建，包含以下组件：

```cpp
namespace kal_controller {
    class Controller {
        // 主要控制接口
        ControlCommand getControlCommand(const Pose& vehiclePose, 
                                       const Trajectory& trajectory, 
                                       bool returnDebugInfo = false);
        
        // 参数配置
        void setParameters(const Parameters& parameters);
    };
}
```

### 控制算法

控制器实现了多层控制方法：

1. **前馈控制**: 使用路径曲率进行预测转向
2. **横向反馈**: 通过自适应增益修正横向误差
3. **角度反馈**: 保持正确的航向对齐
4. **预测组件**: 预测未来路径需求
5. **低通滤波**: 平滑控制输出

### 数学基础

控制律结合了多个组件：

```
u = κ_ff - K_d(e_lat + e_pred) - K_θ(e_θ)
```

其中：
- `κ_ff`: 前馈曲率项
- `K_d`: 自适应横向增益（速度相关）
- `K_θ`: 自适应角度增益（速度相关）
- `e_lat`: 横向位置误差
- `e_pred`: 预测横向误差
- `e_θ`: 航向角误差

## 🚀 快速开始

### 安装

此包专为 ROS/Catkin 工作空间设计：

```bash
cd ~/catkin_ws/src
git clone <repository-url> kal_controller
cd ~/catkin_ws
catkin build kal_controller
```

### 依赖项

- **Eigen3**: 线性代数运算
- **C++14**: 现代 C++ 特性
- **gtest** (测试): 单元测试框架

### 基本用法

```cpp
#include "kal_controller/controller.hpp"
#include "kal_controller/types.hpp"

using namespace kal_controller;

// 1. 创建控制器实例
Controller controller;

// 2. 配置参数
Parameters params;
params.kAngle = 2.0;              // 角度误差权重
params.kDistance = 1.0;           // 横向误差权重  
params.lookAheadIndex = 5;        // 前瞻点数
params.minVelocityThreshold = 0.1; // 最小速度 (m/s)
params.steeringAngleMax = 0.52;   // 最大转向角 (弧度, ~30°)
params.wheelBase = 2.7;           // 车辆轴距 (m)

controller.setParameters(params);

// 3. 获取控制命令
Pose vehiclePose = getCurrentVehiclePose();
Trajectory trajectory = getPlannedTrajectory();

ControlCommand cmd = controller.getControlCommand(vehiclePose, trajectory);

// 4. 应用控制
applyThrottle(cmd.speed);
applySteering(cmd.steeringAngle);
```

### 带调试信息的高级用法

```cpp
// 启用调试信息
ControlCommand cmd = controller.getControlCommand(vehiclePose, trajectory, true);

if (cmd.debugInfo) {
    auto debug = *cmd.debugInfo;
    
    std::cout << "曲率: " << debug.curvature << std::endl;
    std::cout << "横向误差: " << debug.errorSignedDistance << std::endl;
    std::cout << "角度误差: " << debug.errorAngle << std::endl;
    std::cout << "前瞻点: " << debug.lookAheadPoint.transpose() << std::endl;
}
```

## ⚙️ 配置

### 参数调优指南

| 参数 | 描述 | 典型范围 | 调优建议 |
|-----------|-------------|---------------|-------------|
| `kAngle` | 角度误差权重 | 1.0 - 5.0 | 更高的值 → 更激进的航向修正 |
| `kDistance` | 横向误差权重 | 0.5 - 2.0 | 更高的值 → 更紧密的路径跟踪 |
| `lookAheadIndex` | 基础前瞻点数 | 3 - 10 | 更高的值 → 更平滑但响应性较差 |
| `minVelocityThreshold` | 速度阈值 | 0.05 - 0.2 | 低于此速度时，车辆停止 |
| `steeringAngleMax` | 最大转向角 | 0.3 - 0.7 弧度 | 取决于车辆的物理限制 |
| `wheelBase` | 车辆轴距 | 2.0 - 3.5 m | 必须匹配实际车辆几何尺寸 |

### 性能优化

- **高速场景**: 减少 `kAngle` 和 `kDistance` 以提高稳定性
- **急弯**: 增加 `lookAheadIndex` 以实现更平滑的转弯  
- **低速操控**: 增加增益以获得更灵敏的控制
- **噪声轨迹**: 内置滤波有帮助，但建议考虑轨迹平滑

## 🧪 测试

运行综合单元测试套件：

```bash
# 构建并测试
catkin build kal_controller --catkin-make-args tests

# 运行测试  
rosrun kal_controller kal_controller-test

# 或者使用 catkin 工具
catkin test kal_controller
```

测试套件包括：
- 参数验证测试
- 控制算法验证
- 边界情况处理
- 性能基准测试

## 📊 调试和可视化

控制器提供丰富的调试信息：

```cpp
struct DebugInfo {
    Position closestPointOnTrajectory;  // 最近的轨迹点
    Position lookAheadPoint;            // 当前前瞻目标
    double anglePath;                   // 路径方向角
    double curvature;                   // 前瞻处的路径曲率
    double errorAngle;                  // 航向误差 (弧度)
    double errorSignedDistance;         // 横向距离误差 (m)
    double yawVehicle;                  // 当前车辆航向
};
```

使用此信息进行：
- 控制性能分析
- 参数调优
- RViz/绘图工具中的可视化
- 系统诊断

## 🤝 贡献

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/amazing-improvement`)
3. 进行修改并添加相应测试
4. 确保所有测试通过 (`catkin test kal_controller`)
5. 提交 Pull Request

### 代码规范

- 遵循 Google C++ 编码规范
- 使用 clang-format 进行统一格式化
- 为新功能添加全面的单元测试
- 使用 Doxygen 注释记录公共 API

## 📚 参考资料

- [车辆行为生成 - KIT 讲座](https://www.mrt.kit.edu/lehre_WS_Verhaltensgenerierung_Fahrzeuge.php)
- Coulter, R.C. (1992). Implementation of the Pure Pursuit Path Tracking Algorithm
- Snider, J.M. (2009). Automatic Steering Methods for Autonomous Automobile Path Tracking

## 📄 许可证

本项目采用 BSD 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 👥 作者与维护者

- **Nick Le Large** - *初始工作和维护* - [nick.lelarge@kit.edu](mailto:nick.lelarge@kit.edu)

## 🔗 相关链接

- [项目仓库](https://gitlab.mrt.kit.edu/kognitive_automobile_labor/shared/kal_controller)  
- [KAL 实验室主页](https://www.mrt.kit.edu/)
- [问题跟踪](https://gitlab.mrt.kit.edu/kognitive_automobile_labor/shared/kal_controller/-/issues)
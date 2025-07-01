# KAL 控制器调参指南

本指南详细介绍了如何调节改进后的KAL路径跟踪控制器参数，以获得最佳的控制性能。

## 📋 目录
1. [快速开始](#快速开始)
2. [参数分类](#参数分类)
3. [调参步骤](#调参步骤)
4. [常见问题诊断](#常见问题诊断)
5. [高级调参技巧](#高级调参技巧)
6. [参数参考值](#参数参考值)

---

## 🚀 快速开始

### 推荐的调参顺序
1. **基础参数设置** → 2. **控制增益调节** → 3. **自适应参数优化** → 4. **滤波器调节**

### 基本调参原则
- 🔧 **一次只调一个参数**
- 📈 **小幅度递增/递减**
- 🧪 **充分测试后再调下一个**
- 📊 **记录每次调参结果**

---

## 📊 参数分类

### 🎯 核心控制参数（最重要）

#### 1. `k_distance` - 横向偏差增益
- **作用**: 控制车辆修正横向偏差的强度
- **默认值**: 3.0
- **调节范围**: 0.5 - 8.0
- **调节规则**:
  - ⬆️ **增大**：横向偏差修正更快，但可能导致振荡
  - ⬇️ **减小**：更平稳，但横向偏差修正较慢

```yaml
# 保守设置（平稳但响应慢）
k_distance: 1.5

# 标准设置（平衡性能）
k_distance: 3.0

# 激进设置（快速响应但可能振荡）
k_distance: 5.0
```

#### 2. `k_angular` - 航向偏差增益
- **作用**: 控制车辆修正航向偏差的强度
- **默认值**: 2.0
- **调节范围**: 0.3 - 6.0
- **调节规则**:
  - ⬆️ **增大**：航向修正更快，转向更敏感
  - ⬇️ **减小**：转向更温和，但航向修正较慢

```yaml
# 温和转向
k_angular: 1.0

# 标准转向
k_angular: 2.0

# 敏感转向
k_angular: 4.0
```

#### 3. `look_ahead_index` - 前视距离索引
- **作用**: 控制控制器的前瞻性（基础前视距离）
- **默认值**: 10
- **调节范围**: 3 - 30
- **重要**: 新的自适应算法会动态调整此值

```yaml
# 短前视（适合低速、急弯）
look_ahead_index: 5

# 标准前视
look_ahead_index: 10

# 长前视（适合高速、缓弯）
look_ahead_index: 20
```

### ⚡ 安全限制参数

#### 4. `steering_angle_max` - 最大转向角
- **作用**: 限制最大转向角，保护车辆机械结构
- **默认值**: 0.3 (约17.2度)
- **调节范围**: 0.1 - 0.6
- **注意**: 根据实际车辆转向能力设置

#### 5. `min_velocity_threshold` - 最小速度阈值
- **作用**: 低于此速度时车辆停止
- **默认值**: 0.2 m/s
- **调节范围**: 0.05 - 1.0

### 🔧 系统参数

#### 6. `control_loop_rate` - 控制频率
- **作用**: 控制器运行频率
- **默认值**: 10 Hz
- **推荐值**: 10-50 Hz
- **注意**: 太高会增加计算负担，太低会降低控制精度

---

## 🛠️ 调参步骤

### 步骤1: 基础验证（5分钟）

1. **启动系统**:
```bash
cd ~/kal_ws
source devel/setup.bash
roslaunch kal demo_path_follower.launch
```

2. **开启调试信息**:
```yaml
publish_debug_info: true
```

3. **观察基础行为**:
- 车辆是否能跟随路径
- 是否有明显的振荡
- 转向是否过于敏感或迟钝

### 步骤2: 横向控制调节（15分钟）

#### 现象诊断与调节：

| 现象 | 原因 | 调节方案 |
|------|------|----------|
| 🔴 车辆偏离路径且不回正 | `k_distance` 太小 | 增加 `k_distance` += 0.5 |
| 🟡 车辆左右摆动振荡 | `k_distance` 太大 | 减少 `k_distance` -= 0.5 |
| 🔵 横向偏差修正缓慢 | `k_distance` 不足 | 逐步增加 `k_distance` |

#### 调节步骤：
```bash
# 1. 设置保守值测试
rosparam set /control/controller/k_distance 1.5

# 2. 观察车辆行为，逐步增加
rosparam set /control/controller/k_distance 2.0
rosparam set /control/controller/k_distance 2.5
# ... 直到找到最佳值
```

### 步骤3: 航向控制调节（15分钟）

#### 现象诊断与调节：

| 现象 | 原因 | 调节方案 |
|------|------|----------|
| 🔴 转弯不足，车辆外推 | `k_angular` 太小 | 增加 `k_angular` += 0.3 |
| 🟡 转弯过度，频繁修正 | `k_angular` 太大 | 减少 `k_angular` -= 0.3 |
| 🔵 直线行驶不稳定 | `k_angular` 过敏感 | 减少 `k_angular` |

### 步骤4: 前视距离优化（10分钟）

#### 场景化调节：

```yaml
# 低速场景（< 1 m/s）
look_ahead_index: 5-8

# 中速场景（1-3 m/s）
look_ahead_index: 8-15

# 高速场景（> 3 m/s）
look_ahead_index: 15-25
```

### 步骤5: 高级参数微调（10分钟）

在代码中的高级参数（需要重新编译才能修改）：

```cpp
// 文件: /home/yzz/kal_ws/src/kal_controller/src/controller.cpp

// 1. 速度自适应系数
speedAdaptiveKDistance = parameters_.kDistance / (1.0 + speed * 0.3);
//                                                          ^^^^ 调节此值
// 增大：高速时增益减少更多（更保守）
// 减小：高速时保持较高增益（更激进）

// 2. 预测控制权重
predictiveError *= 0.3;  // 调节此值
//                ^^^^ 
// 增大：更多考虑未来轨迹（更前瞻）
// 减小：更多关注当前偏差（更保守）

// 3. 滤波器系数
double filteredU = 0.7 * currentU + 0.3 * previousU;
//                ^^^                ^^^
// 第一个系数大：响应快但可能抖动
// 第二个系数大：平滑但响应慢
```

---

## 🔍 常见问题诊断

### 问题1: 车辆振荡摆动

**可能原因**:
- 控制增益过大
- 前视距离不合适
- 轨迹质量差

**解决方案**:
```yaml
# 1. 降低控制增益
k_distance: 1.5    # 从默认3.0降低
k_angular: 1.0     # 从默认2.0降低

# 2. 调整前视距离
look_ahead_index: 15  # 增加前视距离

# 3. 在代码中增加滤波
# 修改滤波器系数为更保守的值：
# double filteredU = 0.5 * currentU + 0.5 * previousU;
```

### 问题2: 转弯不及时

**可能原因**:
- 前视距离太短
- 航向增益太小
- 预测控制权重太低

**解决方案**:
```yaml
# 1. 增加前视距离
look_ahead_index: 20

# 2. 提高航向增益
k_angular: 3.0

# 3. 在代码中增加预测权重
# predictiveError *= 0.5;  // 从0.3增加到0.5
```

### 问题3: 高速不稳定

**可能原因**:
- 速度自适应不够
- 滤波不足
- 控制频率太低

**解决方案**:
```yaml
# 1. 提高控制频率
control_loop_rate: 20

# 2. 在代码中调整速度自适应系数
# speedAdaptiveKDistance = parameters_.kDistance / (1.0 + speed * 0.5);
# 将0.3改为0.5，高速时更保守
```

---

## 🎯 高级调参技巧

### 技巧1: 分段式调参

不同路段使用不同参数组合：

```yaml
# 直道参数
straight_k_distance: 2.0
straight_k_angular: 1.5
straight_look_ahead: 15

# 弯道参数
curve_k_distance: 3.5
curve_k_angular: 2.5
curve_look_ahead: 8
```

### 技巧2: 速度相关的动态调参

在ROS参数服务器中设置速度相关的参数：

```python
# Python示例：动态调参脚本
import rospy

def dynamic_tuning():
    current_speed = get_current_speed()
    
    if current_speed < 1.0:  # 低速
        rospy.set_param('/control/controller/k_distance', 4.0)
        rospy.set_param('/control/controller/look_ahead_index', 6)
    elif current_speed < 3.0:  # 中速
        rospy.set_param('/control/controller/k_distance', 3.0)
        rospy.set_param('/control/controller/look_ahead_index', 10)
    else:  # 高速
        rospy.set_param('/control/controller/k_distance', 2.0)
        rospy.set_param('/control/controller/look_ahead_index', 18)
```

### 技巧3: 实时监控与记录

使用以下命令监控控制性能：

```bash
# 监控控制命令
rostopic echo /anicar/mux/ackermann_cmd_mux/input/path_follow

# 监控调试信息
rostopic echo /control/debug/error_signed_distance
rostopic echo /control/debug/error_angle

# 记录数据进行离线分析
rosbag record -a
```

---

## 📝 参数参考值

### 保守设置（稳定但响应慢）
```yaml
k_distance: 1.5
k_angular: 1.0
look_ahead_index: 15
control_loop_rate: 10
steering_angle_max: 0.25
```

### 标准设置（平衡性能）
```yaml
k_distance: 3.0
k_angular: 2.0
look_ahead_index: 10
control_loop_rate: 15
steering_angle_max: 0.3
```

### 激进设置（快速响应但可能不稳定）
```yaml
k_distance: 5.0
k_angular: 3.5
look_ahead_index: 8
control_loop_rate: 25
steering_angle_max: 0.4
```

### 不同场景的推荐设置

#### 🏁 赛道高速场景
```yaml
k_distance: 2.0
k_angular: 1.5
look_ahead_index: 20
control_loop_rate: 30
```

#### 🏙️ 城市低速场景
```yaml
k_distance: 4.0
k_angular: 3.0
look_ahead_index: 6
control_loop_rate: 15
```

#### 🌄 山路弯道场景
```yaml
k_distance: 3.5
k_angular: 2.8
look_ahead_index: 8
control_loop_rate: 20
```

---

## 🚨 注意事项

### ⚠️ 安全提醒
- 调参过程中确保车辆在安全区域内
- 始终有紧急停止机制
- 不要同时调节多个参数
- 记录每次调参的效果

### 📚 调参记录模板
```
日期: ______
测试场景: ______
参数修改: 
  - k_distance: 旧值___ → 新值___
  - k_angular: 旧值___ → 新值___
效果评价: ______
下一步计划: ______
```

### 🔄 调参流程图
```
开始 → 基础验证 → 横向调节 → 航向调节 → 前视优化 → 高级微调 → 测试验证 → 完成
  ↑                                                                      ↓
  ←←←←←←←←←←←←←← 如果效果不理想，回到相应步骤 ←←←←←←←←←←←←←←←←←←
```

---

**💡 调参成功的标志**:
- ✅ 车辆平稳跟随路径
- ✅ 横向偏差小于10cm
- ✅ 转向平滑无振荡
- ✅ 不同速度下表现一致
- ✅ 对轨迹噪声不敏感

**祝你调参顺利！** 🎉

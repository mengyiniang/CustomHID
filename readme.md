# 说明
## 开发工具
- STM32CubeMX
- KEIL 5.37 / CLion 2021.3.3
## 硬件
### STM32L053R8
- PA14 SYS_SWCLK
- PA13 SYS_SWDIO
- PA12 USB_DP
- PA11 USB_DM
- PA3 - PA0 GPIO_EXIT (测试用)
## 功能
### 基于STM32L053R8的USB外设 构建HID协议栈 将设备枚举成为HID复合设备 其中包括:
- HID鼠标 (端口:0x82)
- HID键盘 (端口:0x83 report ID: 2)
- HID System Control(System Power Down, System Sleep,System Wake Up) (端口:0x83 report ID: 3) 
- Custom HID (用于上位机发送指令)
## Custom HID指令接口
### VID: 0x0484
### PID: 0x5750
### USAGE_PAGE: 0xff00
### 端口:0x81    
### 长度:16字节
### 字节描述表:
### Byte[3 : 0] - 鼠标
  - Byte[0]
    - bit0 鼠标左键 按下为1
    - bit1 鼠标右键 按下为1
    - bit2 鼠标中键 按下为1
  - Byte[1] 鼠标 x
  - Byte[2] 鼠标 Y
  - Byte[3] 保留
### Byte[12 : 4] - 键盘
  - Byte[4] report ID 固定值为2
  - Byte[5]
    - bit0  Left Control 按下为1
    - bit1  Left Shift 按下为1
    - bit2  Left Alt 按下为1
    - bit3  Left GUI 按下为1
    - bit4  Right Control 按下为1
    - bit5  Right Shift 按下为1
    - bit6  Right Alt 按下为1
    - bit7  Right GUI 按下为1
  - Byte[11 : 6] 键盘对应键值 发送对应值表示对应按键按下 (可依照 USB HID Keyboard/Keypad Page)
### Byte[13 : 12] System Control 
  - Byte[12] report ID 固定值为3
  - Byte[13]
  - bit0: System Power Down 按下为1
  - bit1: System Sleep 按下为1
  - bit2: System Wake Up 按下为1
### Byte[15 : 14] 保留
### 当有按键状态发生改变时直接发送对应状态即可 
#### 举例1a: 鼠标左键按下 发送 
- ***0x01***, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
#### 举例1b: 鼠标左键释放 发送
- ***0x00***, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
#### 举例2a: 键盘a键按下  发送
- 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, ***0x04***, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00
#### 举例2b: 键盘a键释放  发送
- 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, ***0x00***, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00

# ESPINO32-Differential-Drive-WebControl

<p align="center">
  <img src="twoWheelRobot.jpg" width="400">
</p>

https://youtu.be/6cGIzCCgsug

ESPINO32 Differential Drive Web Control
หุ่นยนต์สมาร์ทคาร์ขับเคลื่อนแบบ 2 ล้อ (Differential Drive) ควบคุมผ่านหน้าเว็บ Dashboard โดยใช้ ESP32 (ESPino32) เป็นหน่วยประมวลผลหลัก และใช้ระบบปฏิบัติการ FreeRTOS ในการจัดการภารกิจแบบขนาน

🛠 อุปกรณ์ที่ใช้ (Hardware Requirements)
Microcontroller: ESPino32 (ESP-WROOM-32)

Motor Driver: L298N Dual H-Bridge Motor Driver

Power Source: แบตเตอรี่ Li-ion 18650 จำนวน 2 ก้อน (7.4V)

Chassis: โครงรถหุ่นยนต์ (Smart Car Chassis) พร้อมมอเตอร์ DC 2 ตัว

Breadboard & Jumper Wires: สำหรับการเชื่อมต่อวงจร

<p align="center">
  <img src="webControl.png" width="400">
</p>

Dashboard UI & Hardware Integration ภาพรวมการทำงานของระบบควบคุมหุ่นยนต์ผ่าน WiFi Access Point:

UI Design: ใช้ HTML/CSS/JS สร้างหน้าเว็บรีโมทที่รองรับระบบ Multi-touch (กดค้างวิ่ง-ปล่อยหยุด)

Speed Control: ส่งค่าความเร็วผ่าน HTTP Request ไปเปลี่ยนตัวแปร PWM ใน ESP32 แบบ Dynamic

Power System: จ่ายไฟจาก L298N (5V Out) เข้าขา Vin ของ ESPino32 เพื่อความปลอดภัยและประหยัดพื้นที่

Processing: ใช้ศักยภาพของ ESP32 ในการรัน Web Server ที่ Core 0 เพื่อไม่ให้รบกวน Loop การควบคุมมอเตอร์ที่ Core 1"

<p align="center">
  <img src="wiring_diagram.png" width="600">
</p>
การเชื่อมต่อสายไฟ (Wiring Details)
Power System (ระบบพลังงาน)
Battery (+): ต่อเข้ากับช่อง +12V ของโมดูล L298N (สายสีแดง)

Battery (-): ต่อเข้ากับช่อง GND ของโมดูล L298N (สายสีดำ)

Common Ground: มีการเชื่อมต่อ GND ระหว่าง L298N และ ESP32 เพื่อให้ระบบใช้ Ground ร่วมกัน (สายสีดำ)

Logic Power: จ่ายไฟ +5V จากโมดูล L298N ไปยังพิน 5V ของ ESP32 (สายสีส้ม)

Motor Driver Control (การควบคุมมอเตอร์)
การควบคุมความเร็ว (PWM) และทิศทาง เชื่อมต่อผ่านขา GPIO ของ ESP32 ดังนี้:

Motor A (ซ้าย):

ENA: ต่อกับ ESP32 (สายสีเขียว - สำหรับคุมความเร็ว)

IN1 / IN2: ต่อกับ ESP32 (สายสีเหลือง/น้ำเงิน - สำหรับคุมทิศทาง)

Motor B (ขวา):

ENB: ต่อกับ ESP32 (สายม่วง - สำหรับคุมความเร็ว)

IN3 / IN4: ต่อกับ ESP32 (สายสีขาว/ฟ้า - สำหรับคุมทิศทาง)

Motor Outputs (เอาต์พุตไปยังมอเตอร์)
OUT1 & OUT2: ต่อเข้ากับมอเตอร์ตัวที่ 1 (สายสีน้ำตาล)

OUT3 & OUT4: ต่อเข้ากับมอเตอร์ตัวที่ 2 (สายสีน้ำตาล)

<p align="center">
  <img src="overView.png" width="600">
</p>

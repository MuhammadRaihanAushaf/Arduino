Sistem Deteksi Pencemaran Udara IoT Sederhana

Deskripsi Proyek:
Proyek ini adalah sistem deteksi pencemaran udara berbasis IoT yang menggunakan sensor gas dan suhu untuk memantau kualitas udara secara real-time. Data yang diperoleh dapat ditampilkan pada LCD, modul 7-segmen, atau dikirim ke Telegram untuk pemantauan jarak jauh.
Sistem ini dapat mendeteksi gas berbahaya seperti karbon monoksida (CO) dan gas mudah terbakar menggunakan sensor MQ-2 dan MQ-7. Jika tingkat pencemaran udara melebihi ambang batas, buzzer dan LED akan menyala sebagai peringatan.

Komponen yang Digunakan:
Arduino (Mega2560) – sebagai mikrokontroler utama
Sensor MQ-2 – mendeteksi asap
Sensor MQ-7 – mendeteksi karbon monoksida (CO)
Sensor DHT – mengukur suhu dan kelembaban udara
LCD I2C 20x4 – menampilkan data kualitas udara
TM1637 7-Segment Display – menampilkan waktu
RTC DS3231 – melakukan perhitungan waktu
LED Merah – indikator pencemaran udara
Buzzer – alarm peringatan jika asap polusi terdeteksi
ESP8266 - Mengirim data dan perintah antara telegram dan arduino mega2560

Cara Kerja:
1. Sensor mendeteksi kualitas udara dan mengirimkan data ke Arduino.
2. Arduino memproses data dan membandingkannya dengan ambang batas yang telah ditentukan.
3. Jika kualitas udara buruk, LED dan buzzer akan menyala sebagai alarm.
4. Data ditampilkan pada LCD dan/atau modul 7-segmen.
5. Data dapat dikirim ke Telegram untuk pemantauan jarak jauh.

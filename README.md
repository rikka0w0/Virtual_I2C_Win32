# Virtual_I2C_Win32

This program simulates a I2C bus using COM port. This program can be used to download data into an EEPROM, or test any new chips.
USB to COM adapters are supported.

This project is created using Visual Studio 2015, C++.
Minimum supported system: Windows XP

Standard I2C communaction procedure(Host):
Write(Tx):
1. Send START
2. Send device address, LSB = 0 (Write)
3. Wait answer from slave device (ACK or NACK)
4. Send register address, may be 1 or 2 byte, depends on the device
5. Wait answer from slave device
6. Send data
7. Wait answer from slave device
8. Repeat 6 and 7 if there are more data to send
9. Send STOP and release the I2C bus

Read(Rx):
1. Send START
2. Send device address, LSB = 0 (Write)
3. Wait answer from slave device (ACK or NACK)
4. Send register address, may be 1 or 2 byte, depends on the device
5. Wait answer from slave device
6. Send START
7. Send device address, LSB = 1 (Read)
8. Wait answer from slave device
9. Supply a clock on SCL, receive 1 byte of data from SDA
10. Send ACK to the slave device (ignore this step if this byte is the only byte or the last byte)
11. Repeat 9 and 10 if there are more data to receive
12. Send STOP and release the I2C bus

Attention:
Some communication will fail since the simulated I2C bus is very slow, the maximum SCL frequency is around 1KHz, so the maximum data rate is 1kbps

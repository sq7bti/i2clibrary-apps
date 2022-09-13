# i2clibrary-apps
i2c.library user applications

A collection of tools to perform basic operations on I2C bus.

i2cdetect - scan i2c bus
i2cset - send write request to i2c slave device
i2cget - query read from slave device
hwmon - example code with multiple reads to output status of sensors connected at fixed addresses
lm75 - read LM75 temperature sensor chip
lm75th - set threshold for alarm in LM75 sensor chip

i2cset - usage: A=Address/A,V=Value/A/M
i2cget - usage: A=Address/A,L=Length/N,D=Decimal/S

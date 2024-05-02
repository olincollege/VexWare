
# test_script.ps1

$portName = "COM5"
$baudRate = 9600

# Create SerialPort object
$serialPort = New-Object System.IO.Ports.SerialPort $portName, $baudRate

while ($true) {
# Open serial port
$serialPort.Open()

# Define integer
$integer = 1

# Convert integer to bytes
$bytes = [BitConverter]::GetBytes($integer)

# Send bytes over serial
$serialPort.Write($bytes, 0, $bytes.Length)

# Close serial port
$serialPort.Close()

}
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""BinSerial is a library to transmit data structure in binary via serial link.

TODO:
- Finish Documentation.
- Check if compatible with multi-treading.
- Catch potential exceptions?

"""

__all__ = ['BinSerial']
__version__ = '1.0'
__author__ = 'Jonathan Plasse'

# For serial connection
import serial
# To convert binary data
import struct
import time
import argparse


class BinSerial:
    """Send and Receive serial data in binary."""

    def __init__(self, port_name, baud_rate):
        """Open a serial link at port_name with baud_rate."""
        # Dict to convert explicit types to format caracters
        self.format_dict = {'char': 'c', 'bool': '?',
                            'int8': 'b', 'uint8': 'B',
                            'int16': 'h', 'uint16': 'H',
                            'int32': 'i', 'uint32': 'I',
                            'int64': 'q', 'uint64': 'Q',
                            'float': 'f', 'double': 'd'}
        # Port name of the serial port
        self.port_name = port_name
        # Baud rate of the connection
        self.baud_rate = baud_rate

        # Open serial link
        self.ser = serial.Serial(self.port_name, self.baud_rate, timeout=1)

        # Wait for initialization
        time.sleep(2)

    def __del__(self):
        """Close serial link."""
        self.ser.close()

    def _compute_format(self, struct_format):
        """Compute the format caracters from struct_format.

        struct_format -- array of the struct types
                         (see keys BinSerial.format_dict)
        """
        # Set byte order to native and no alignement for the binary data
        format_caracters = '='

        # Convert struct_format explicit types to format caracters
        for t in struct_format:
            format_caracters += self.format_dict[t]

        return format_caracters

    def read(self, struct_format):
        """Read data from serial link with struct_format.

        struct_format -- array of the struct types
                         (see keys BinSerial.format_dict)

        Return:
        data -- array containing the data read
        """
        # Compute the format caracters
        format_caracters = self._compute_format(struct_format)
        # Calculate the number of bytes needed
        nb_bytes = struct.calcsize(format_caracters)

        # Read requested data
        raw_data = b""
        while len(raw_data) < nb_bytes:
            raw_data += self.ser.read(nb_bytes - len(raw_data))

        # Convert the raw data
        data = list(struct.unpack(format_caracters, raw_data))

        return data

    def write(self, struct_format, data):
        """Write data to serial link with struct_format.

        struct_format -- array of the struct types
                         (see keys BinSerial.format_dict)
        data -- array containing the data to write
        """
        # Compute the format caracters
        format_caracters = self._compute_format(struct_format)

        # Convert data in binary
        raw_data = struct.pack(format_caracters, *data)
        # Send raw_data
        self.ser.write(raw_data)


if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument("-p", "--port-name", default='/dev/ttyACM0',
                    help="Port name of the serial port")
    args = vars(ap.parse_args())

    port_name = args['port_name']
    baud_rate = 9600

    # Define the format of the structure of the data
    struct_format = ['float']*3

    # Initialize connection
    bser = BinSerial(port_name, baud_rate)

    while(True):
        data = bser.read(struct_format)
        print(data)

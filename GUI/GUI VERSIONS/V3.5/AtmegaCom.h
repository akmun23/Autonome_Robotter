#pragma once

// library headers
#include <stdio.h>
#include <string.h>
#include <iostream>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()



class AtmegaCom
{
private:

    int _serial_port;

public:
    AtmegaCom();
    void sendmsg(char InputNumber);
};






#include "AtmegaCom.h"
    bool atmegaCom(char InputNumber){

    int serial_port = open("/dev/ttyUSB0", O_RDWR);                     // Her åbner vi serie port forbindelsen

    // Check for errors
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));     // Her tjekker vi for om den har fundet en forbindelse til porten
    }

    struct termios tty;                                                 // Her benytter vi structen termios som er en inbygget struct i linux til at konfigurere vores port
    if(tcgetattr(serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }


    tty.c_cflag &= ~PARENB;                                             // Her slår vi parity bit fra

    tty.c_cflag &= ~CSTOPB;                                             // Sætter at der skal være 1 stop bit

    tty.c_cflag &= ~CSIZE;                                              // Clear alle size bit og bruger den næste linje til at sætte størrelsen på dataen
    tty.c_cflag |= CS8;                                                 // Her sætter vi vores port til at bruge 8 bits data

    tty.c_cflag &= ~CRTSCTS;                                            // Disable RTS/CTS som betyder at man har 2 ekstra ledninger til at fortælle hvornår den skal sende og modtage det har vi ikke så den er slået fra


    tty.c_cflag |= CREAD | CLOCAL;                                      // CREAD betyder at vi kan læse fra porten og CLOCAL betyder at vi ignorerer modem control lines

    tty.c_lflag &= ~ICANON;                                             // Her slår vi canonical mode fra som betyder at vi læser en byte ad gangen

    // De her 3 ting burde ikke være nødvendige at slå fra da de bruges af canonical mode men de slås fra for en sikkerheds skyld
    tty.c_lflag &= ~ECHO;                                               // Disable echo
    tty.c_lflag &= ~ECHOE;                                              // Disable erasure
    tty.c_lflag &= ~ECHONL;                                             // Disable new-line echo

    tty.c_lflag &= ~ISIG;                                               // Her slår vi fra at serial porten læser de her komandoer ud fra dataen INTR, QUIT and SUSP

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                             // Her slår vi software flow control fra

    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);    // Her slår vi fra at der skal være speciel behandling af input bytes vi vil bare have dem som de er dejlig rå data

    tty.c_oflag &= ~OPOST;                                              // Her fjerner vi speciel tolkelse af output data som fx newline chars
    tty.c_oflag &= ~ONLCR;                                              // Igen bare at vi fortsætter med at fjerne special tolkelse af output data

    // Måske skal vi køre på timer istedet i forhold til at måle strøm
    tty.c_cc[VTIME] = 0;                                                // Her sætter vi timeout til 0 så den venter ikke på at der kommer noget data i forhold til tid hvis den ikke får noget data så går den videre
        // men hvis den får data indenfor intervaller af timeout fortsætter den

    tty.c_cc[VMIN] = 1;                                                 // Venter på at mindst 1 byte er læst ind før den går videre altså den venter her for evigt indtil den får en byte data


    cfsetispeed(&tty, B9600);                                           // Sætter in og output baud rate til 9600
    cfsetospeed(&tty, B9600);


    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {                   // Gemmer de nye settings vi har defineret indtil nu og tjekker for fejl
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }

    char msg[] = {InputNumber};                                         // Her skriver vi vores besked til atmegaen
    write(serial_port, msg, sizeof(msg));

    char read_buf [1];                                                  // Her laver vi en buffer til at læse data ind i


    int n = read(serial_port, &read_buf, sizeof(read_buf));             // Her læser vi data ind fra atmegaen i variablen n

    std::cout << std::endl;
    printf("Read %i bytes. Received message: %s", n, read_buf);         // Her printer vi hvor mange bytes vi har læst og hvad vi har læst
    std::cout << std::endl;




    return true;

    close(serial_port);
}




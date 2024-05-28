#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("/dev/tty", O_RDWR); // Otwórz plik urządzenia terminalu
  if (fd < 0) {
    printf("Błąd otwarcia pliku urządzenia terminalu\n");
    return 1;
  }

  struct termios options; // Struktura do przechowywania parametrów terminala
  tcgetattr(fd, &options); // Odczytaj aktualne parametry terminala

  // Zmień parametry terminala (np. szybkość transmisji)

  tcsetattr(fd, TCSANOW, &options); // Ustaw zmodyfikowane parametry terminala

  close(fd); // Zamknij plik urządzenia terminalu

  return 0;
}

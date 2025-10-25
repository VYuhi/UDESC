class Semaphore {
  //variaveis
  private:
    int greenPin;
    int yellowPin;
    int redPin;

  //construtor
  public:
    Semaphore(int pinG, int pinY, int pinR){

      greenPin = pinG;
      yellowPin = pinY;
      redPin = pinR;

      pinMode(greenPin, OUTPUT);
      pinMode(yellowPin, OUTPUT);
      pinMode(redPin, OUTPUT);
    }

    //desliga todos
    void AllOff() {

      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
    }

    //liga o verde
    void OnGreen() {

      AllOff();
      digitalWrite(greenPin, HIGH);
      delay(1500);
    }

    //liga o amarelo
    void OnYellow() {

      AllOff();
      digitalWrite(yellowPin, HIGH);
      delay(1500);
    }

    //liga o vermelho
    void OnRed() {

      AllOff();
      digitalWrite(redPin, HIGH);
      delay(1500);
    }
};

//cria os semaforos como objetos
Semaphore semaphore1(2, 3, 4);
Semaphore semaphore2(6, 7, 8);


class Mediator {

  //variaveis
  private:
    int status = 1;
  
  //inicia o funcionamento do semaforo
  public:
    void startSemaphore(Semaphore &sema1, Semaphore &sema2) {
      
      if(status == 1){
        sema1.OnGreen();
        sema1.OnYellow();
        sema1.OnRed();
        
        status = 2;
      } else if (status == 2){
        sema2.OnGreen();
        sema2.OnYellow();
        sema2.OnRed();

        status = 1;
      }
  }
};

//objeto mediator
Mediator mediator;

void setup() {
}

void loop() {
  // chama a inicialização dos semaforos
  mediator.startSemaphore(semaphore1, semaphore2);
}
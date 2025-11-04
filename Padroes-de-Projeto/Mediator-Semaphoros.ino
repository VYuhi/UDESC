class Semaphore {
  // variaveis
  private:
    
    int greenPin, yellowPin, redPin;
    int lightIntensity=255;

  // construtor 
  public:
    Semaphore(int pinG, int pinY, int pinR) {
      greenPin = pinG;
      yellowPin = pinY;
      redPin = pinR;
      pinMode(greenPin, OUTPUT);
      pinMode(yellowPin, OUTPUT);
      pinMode(redPin, OUTPUT);

      OnRed();
    }

    void AllOff() {
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
    }

    // liga o verde
    void OnGreen() {
      AllOff();
      analogWrite(greenPin, lightIntensity);
    }

    // liga o amarelo
    void OnYellow() {
      AllOff();
      analogWrite(yellowPin, lightIntensity);
    }

    // liga o vermelho
    void OnRed() {
      AllOff();
      analogWrite(redPin, lightIntensity);
    }

    void maintenance(int time) {
      OnYellow();
      delay(time);
      AllOff();
      delay(time);
    }

    void setLightIntensity(float lightIntensity) {
      this->lightIntensity = (int)lightIntensity;
    }
};

// cria os semaforos como objetos
Semaphore semaphore1(3, 5, 6);
Semaphore semaphore2(9, 10, 11);

// central eletrica
class CentralEnergy {
  private:
    float lightIntensity;
    bool maintenance;

  public:
    CentralEnergy(float lightIntensity) {
      this->lightIntensity = (lightIntensity * 2.55);
      maintenance = true;
    }

    float getLightIntensity() {
      return lightIntensity;
    }

    bool getMaintenance() {
      return maintenance;
    }
};

// colocar em porcentagem a energia
CentralEnergy centralEnergy(100);

class SignalCross {
  private:
    int redPin;
    int greenPin;

    bool isPressed;

  public:
    SignalCross(int greenPin, int redPin) {
      this->greenPin = greenPin;
      this->redPin = redPin;
      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
      redLight();

      isPressed = false;
    }

    void greenLight() {
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, HIGH);
    }

    void redLight() {
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
    }

    void isPress(int time) {

      if(isPressed) {

        greenLight();
        delay(time);
        redLight();

        isPressed = false;
      }
    }
};

SignalCross signalCross(A4, A5);

class IMediator {

  public:
    virtual void startSystem(Semaphore &s1, Semaphore &s2, CentralEnergy &ce, SignalCross &sc) = 0;
};

class Mediator : public IMediator {
  // variaveis
  private:
    int order = 1;
    float lightIntensity;

  public:
    // inicia o funcionamento do sistema
    void startSystem(Semaphore &sema1, Semaphore &sema2, CentralEnergy &centralEnergy, SignalCross &signalCross) {

      // controle da intensidade do led
      lightIntensity = centralEnergy.getLightIntensity();
      
      //aciona a manutenção eletrica
      if (centralEnergy.getMaintenance()) {
        sema1.maintenance(600);
        sema2.maintenance(600);
        return;
      }

      // liga o semaforo
      Semaphore* semaphore = (order == 1) ? &sema1 : &sema2;
      
      start(semaphore);

      //semaphore->start(1500, 1500, 1500, lightIntensity);
      order = (order==1) ? 2 : 1;

      // verifica se se o botao foi pressionado
      signalCross.isPress(1500);
    }

    void start(Semaphore* semaphore) {

      semaphore->OnGreen();
      delay(1500);

      semaphore->OnYellow();
      delay(1500);

      semaphore->OnRed();
      delay(1500);
    }
};

// objeto mediator
Mediator mediator;

void setup() {
}

void loop() {
  // chama a inicialização dos semaforos
  mediator.startSystem(semaphore1, semaphore2, centralEnergy, signalCross);
  delay(100);
}

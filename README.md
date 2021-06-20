# tube-clock
下に日本語の説明あります。
## A florescent display clock using NEC LD8035E tubes
Designed using no ICs other than a PSOC5LP microcontroller and transistor arrays for simplicity and size.

この時計はNECのLD8035Eという蛍光表示管を使用し、PSOC5LPというマイコンのおかげで使用の部品も少ないです。
![20210603_234007](https://user-images.githubusercontent.com/85288181/120663858-6199c180-c4c5-11eb-8b98-5e14e62ac25e.jpg)

The project consists of 3 main blocks; the microcontroller, the tubes and drivers, and a step-up voltage converter. florescent tubes require a fairly high voltage of 12 - 20 volts to operate.

PSOC5LPはマイコンだけでなく、内臓にCPLDのような機能とプログラマブルアナログ回路も入っています。
このプロジェクトのセブンセッグのドライバーと、RTCと、スイッチのdebouncerも全部ハードに設計したのでプロセッサーの負担は軽い。
蛍光表示管を光らせるため、１２Ｖ以上は必要ですが、USBの５Ｖだけで使いたかったので、ステップアップコンバーターを設計しました。
シンプルな設計ですが、蛍光表示管にして十分です。
![PSOC Internal and Boost circuitry](https://user-images.githubusercontent.com/85288181/120659266-2a291600-c4c1-11eb-9cdf-f9505c6626f5.png)

The diagram above shows the internal configuration inside of the PSOC5LP and the external connections to the boost converter. (shown with blue wires) The pwm timer inside of the microcontroller signals the ADC to sample the output voltage of the step-up converter and adjust its. There is no sophisticated control system in the code so it has room for improvement.　Much of the design is in the hardware of the microcontroller and not in the code due to the one-of-a-kind design of Cypress Semiconductor's PSOC series of microcontrollers with CPLD like configurable hardware and an analog routing system.

The tubes and drivers are fed from the step-up voltage converter, and the heaters are run directly from 5 volts. The drivers are source side drivers that are connected to the grids and the segments of the tubes giving the microcontroller control over all the displays.

コンバーターの制御はパルス幅変調で、２０usごとにマイコンは出力を計り、パルス幅変調のデューティ比を変わります。
蛍光表示管のグリッドとセグメントはTD62783ソースドライバに繋ぎ、トランジスタのゲートはマイコンに繋いでいます。

![20210528_083957](https://user-images.githubusercontent.com/85288181/120909007-37a1f400-c6ab-11eb-806e-b5e873325562.jpg)

Code for this project can be downloaded here.

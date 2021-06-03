# tube-clock
## A florescent display clock using NEC LD8035E tubes
Designed using no ICs other than a PSOC5LP microcontroller and transistor arrays for simplicity and size.
![20210603_234007](https://user-images.githubusercontent.com/85288181/120663858-6199c180-c4c5-11eb-8b98-5e14e62ac25e.jpg)

The project consists of 3 main blocks; the microcontroller, the tubes and drivers, and a step-up voltage converter. florescent tubes require a fairly high voltage of 12 - 20 volts to operate
![PSOC Internal and Boost circuitry](https://user-images.githubusercontent.com/85288181/120659266-2a291600-c4c1-11eb-9cdf-f9505c6626f5.png)
The diagram above shows the internal configuration inside of the PSOC5LP and the external connections to the boost converter. (shown with blue wires) The pwm timer inside of the microcontroller signals the ADC to sample the output voltage of the step-up converter and adjust its. There is no sophisticated control system in the code so it has room for improvement.

The tubes and drivers are fed from the step-up voltage converter, and the heaters are run directly from 5 volts. The drivers are source side drivers that are connected to the grids and the segments of the tubes giving the microcontroller control over all the displays.

Much of the design is in the hardware of the microcontroller and not in the code due to the one-of-a-kind design of Cypress Semiconductor's PSOC series of microcontrollers. All of the hardware implementation is shown above in the circuit diagram.

Code for this project can be downloaded here.

# arduino-thermometer_by_defi_sensor
Thermometer by Defi sensor for arduino.

![w](https://user-images.githubusercontent.com/11486268/66576894-72404a00-ebb3-11e9-85b9-71a46f9ab2dd.JPG)

## The sensor characteristics
### PDF00903S - Temp

```
R25ºC = 10000[Ω]
B = 3380[K]
```

### PDF00703S - Press

```
Vo = {analog value} * 5v / 1024 # arduino 10bit(0~1024)
n[KPa]  = 250(Vo - 0.480) * 0.0101972
```

#### eq.
![eq](https://user-images.githubusercontent.com/11486268/62881604-2025a880-bd6b-11e9-86f2-68b08cad765c.png)

#### Wiring(WIP, MEMO)
![w](https://user-images.githubusercontent.com/11486268/66576965-8b48fb00-ebb3-11e9-90f6-d7e31e2f95d8.JPG)

## Todo
https://github.com/puriso/arduino-thermometer_by_defi_sensor/issues

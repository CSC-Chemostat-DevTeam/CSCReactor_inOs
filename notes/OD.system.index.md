## User Hightlites
- automatic-gain-controlled, dual-beam photometer
- we have made experiments and the curve laser input PWM vs TSL235R pulses conted is lineal
    - I mean, we are working in a region far from saturation
    - of both, the sensor, and the Arduino frequency alg
- We need to have >10 sensor connected
    - we can't use interruptions
- At the moment we can't get other electronics
    - but it is nice to know same price range alternative 
        - for the future

## Goal Context
- Extract the best sensibility from the electronic setup for turbidity/OD measurement.
- Brainstorming around laser–sensor architecture, detection limits, counting methods, electronics constraints, and sensitivity optimization.

## TSL235R Characteristics
- Frequency-output photodiode.
- Frequency ∝ irradiance (linear region).
- Practical frequency range ~0–100 kHz (up to ~200–300 kHz typical before nonidealities).
- Pulse counting subject to Poisson noise (√n).
- Sensitivity depends on counts per integration time.

## Arduino Limitations
- `pulseIn` limited to low/mid frequencies (<~10–20 kHz).
- CPU overhead and blocking behavior cause missed pulses at higher frequencies.
- Multi-channel pulse measurement unscalable for 10 sensors.
- Few external interrupts; pin-change interrupts insufficient for high-frequency multi-channel.
- Loop-based or polling-based counting fails at high frequency.

## Multi-Channel Constraints
- >10 TSL235R sensors exceed interrupt capacity.
- High-frequency edges cannot be serviced reliably on many channels.
- Bandwidth and latency limitations make Arduino unsuitable for raw multi-channel pulse capture.
- Requires external counting hardware.

## External Counting Solutions
- Hardware ripple counters (74HC4040, 74HC393) → full-range pulse accumulation.
- Frequency divider / prescaler ICs.
- Dedicated frequency-counter ICs (e.g., ICM7216).
- Small auxiliary MCUs (ATtiny) per 1–2 channels → hardware timers → I2C to main Arduino.
- FPGA/CPLD as multi-channel counter.
- Shift registers (74HC165, CD4021) for reading counter outputs over few pins.
- Hardware counters alleviate Arduino bandwidth issues (related to TSL235R frequency range).

## High-Speed Counting Methods
- Interrupt-based using `attachInterrupt` for single-channel high-frequency counting.
- Global `volatile` pulse counter incremented from ISR.
- Not scalable to 10 channels due to interrupt resource limits.
- External counters handle MHz-level frequencies (related to TSL235R linear range).

## Dual-Beam Architecture (Current Concept)
- Laser beam split into reference arm and sample arm.
- Reference path does not interact with sample.
- Sample path passes through turbidity sample.
- Two TSL235R sensors measure reference and sample frequencies.
- Dual-beam compensates for laser drift and splitter variations.

## Intensity Control / Feedback (AGC)
- Servo laser drive to maintain sample sensor at fixed setpoint frequency.
- Sample detector remains in optimal SNR & linearity region.
- Laser drive increases as turbidity increases (related to transmission T).
- \(I_L ∝ 1/T\) under setpoint control.
- Control variable (laser drive) becomes turbidity proxy.
- Reference sensor frequency also becomes turbidity proxy (∝1/T).
- Allows constant sensitivity around setpoint.

## Sensitivity Considerations
- Sensitivity depends on frequency and counts per integration time.
- Higher laser intensity → higher frequency → higher n → lower relative noise (1/√n).
- Too high intensity → TSL235R nonlinearity or counter saturation.
- Too low intensity → low n → high Poisson noise.
- Sensitivity varies with turbidity due to exponential transmission (related to Beer–Lambert).
- Logarithm of laser drive or reference frequency ~linear in OD.
- Sensitivity is best in mid-range of turbidity; worst at extremes (very clear or very opaque).

## Calibration Implications
- Use ratio `sample/reference` or servo-defined control variable.
- Dual-beam ratio reduces drift, depends on splitter stability.
- Servo mode encodes turbidity in drive current (monotonic).
- Calibration can be linearized by taking log(control variable).
- Requires defining a setpoint where sample sensor SNR is optimal.

## Optical/Turbidity Physics
- Transmission \(T\) = exp(-k c L) (Beer–Lambert).
- Sample frequency \(f_{sam} ∝ I_L T\).
- Reference frequency \(f_{ref} ∝ I_L\).
- Servo sets \(f_{sam} = f_0\) → \(I_L ∝ 1/T\).
- Turbidity information shifts into \(I_L\) and \(f_{ref}\).

## Proposed Improvements (Within Current Architecture)
- Use `_count_pulses3` for single-channel high-speed testing.
- For multi-channel, rely on external counters.
- Consider controlling sample/reference **ratio** instead of absolute sample frequency.
- Tune laser setpoint for best dynamic range.
- Choose integration time T to maintain adequate counts.
- Avoid saturating counters or underexposing sensors.

## Alternative Architectures
- Dual-beam ratio-only measurement (fixed laser, no feedback).
- Photodiode + TIA + ADC approach:
  - Multiple analog channels easier to scale.
  - Avoids high-frequency counting entirely.
  - Higher dynamic range possible with good ADC.
  - Retains dual-beam or AGC concepts in analog domain.
- Modulated source + lock-in detection (more complex, best noise performance).

## Practical Constraints and Trade-Offs
- TSL235R requires robust high-frequency counting; Arduino alone insufficient.
- Servo improves sensitivity but increases electronics complexity.
- External counters add hardware but solve scalability problem.
- Analog solution requires front-end design but simplifies multi-channel scaling.
- SNR and linearity strongly tied to chosen setpoint and integration time.
- Trade-off between simplicity (ratio-only) and precision (servo-based).

# Smart Solar Tracking Umbrella System

An Arduino-based shading structure that automatically rotates its roof to follow the sun, keeping pedestrians shaded throughout the day without any manual adjustment.

Hatem Alfaifi

---

## Abstract

The Smart Solar Tracking Umbrella addresses outdoor discomfort in hot climates by creating a shading system that automatically rotates toward the brightest light source. Using two LDR (light-dependent resistor) sensors and an Arduino-controlled servo motor, the system compares light levels on each side and adjusts the roof's orientation accordingly. Testing confirmed reliable light tracking and smooth response to changes in brightness, demonstrating how simple sensor-based automation can enhance public spaces and reduce heat exposure.

## How It Works

The system uses two LDR sensors — one on each side of the roof — to detect the direction of the strongest light.

1. Each LDR outputs an analog voltage proportional to how much light is hitting it.
2. The Arduino reads both sensors (`A0` and `A1`) and calculates the difference between them.
3. If one side is significantly brighter than the other, the Arduino signals the servo motor to rotate the roof toward that side.
4. If both readings are close enough (within a small threshold), the roof holds its current position — this prevents the servo from jittering back and forth in response to minor light fluctuations (e.g., passing clouds, small shadows).

This closed-loop logic lets the umbrella continuously "chase" the sun using only two sensors and one motor, with no need for pre-programmed sun-path calculations or a real-time clock.

## Hardware / Bill of Materials

| Component | Quantity |
|---|---|
| Arduino Uno | 1 |
| LDR (Light Dependent Resistor) | 2 |
| Servo motor (SG90-class) | 1 |
| Mini breadboard | 1 |
| Dupont jumper wires | ~20 |

**Prototype cost: 230 SAR**

## Code

The repository contains two versions of the control sketch, both using the [`Servo`](https://www.arduino.cc/reference/en/libraries/servo/) library.

### `Moving_Umbrella_V2.ino`

```cpp
int diff = (left) - (right);

if (diff > 20 && servoPos < 40) {
    servoPos += 5;
} else if (diff < -20 && servoPos > 0) {
    servoPos -= 5;
}

myServo.write(servoPos);
delay(20);
```

- Reads the left LDR (`A1`) and right LDR (`A0`).
- Computes `diff = left - right`.
- If the left side is brighter by more than a `20`-unit margin, the servo position increases by `5` degrees per loop (rotating toward the left).
- If the right side is brighter by more than `20` units, the servo position decreases by `5` degrees per loop.
- If the difference is within the `±20` **dead zone**, the servo holds its position — this is what keeps the tracking stable instead of constantly hunting for a perfect balance.
- Moves in coarse `5°` steps for a fast, visibly responsive tracking motion.
- Serial output prints both LDR readings, the difference, and the current servo position for debugging/monitoring.

### `Moving_Umbrella_V2_c2.ino`

Functionally identical tracking logic, with two differences:

- The difference is computed as `diff = right - left` instead of `left - right` (sign convention flipped, with the comparisons inverted to match — the resulting behavior is the same).
- The servo moves in fine `1°` steps (`servoPos++` / `servoPos--`) instead of `5°` jumps, producing smoother, slower motion. This version trades tracking speed for smoothness, and is better suited to a final build where visible jerkiness in the roof movement would be undesirable.

### Movement Limits (Safety Range: 0°–40°)

The servo's range of motion is deliberately restricted to **0°–40°**, rather than the full 0°–180° a standard servo allows. This limit is intentional and serves two purposes:

1. **Pedestrian safety** — The umbrella structure sits above people walking underneath it. If the roof were allowed to tilt too far, it could lower its edge into the space people occupy, creating a collision hazard or blocking the walkway. Capping the tilt at 40° keeps the entire structure clear of the pedestrian zone at all times.
2. **Shading effectiveness** — 40° was chosen because it comfortably covers the sun's angular range during the hours of peak sun intensity (i.e., when shade is actually needed most). Beyond this range, the sun is low enough in the sky that the marginal shading benefit doesn't justify the added mechanical travel and safety risk.

In short: the angle limit isn't a hardware constraint — it's a deliberate design decision balancing tracking coverage against the safety of people below the structure.

## Environmental Impact

| | Strengths | Weaknesses | Mitigation |
|---|---|---|---|
| Space | Reduces sunlight damage on nearby benches/objects | Can require significant space if placed improperly | Keep support pillars thin while maintaining stability |
| Materials | — | Metal pillars can rust over time | Zinc-layer coating on pillars to prevent corrosion |
| Energy | Reduces need for outdoor cooling systems, lowering energy consumption | Electronic components generate manufacturing waste | Use eco-friendly materials where possible |

## Cultural & Social Impact

| | Strengths | Weaknesses | Mitigation |
|---|---|---|---|
| Comfort | Encourages walking outside in hot weather; improves comfort during extended outdoor stays | May cause total light blockage in some spots | Design shade to remain as transparent as possible |
| Health | Reduces need for vehicles on short commutes, cutting pollution | Can interfere with natural scenery / Vitamin D exposure | Leave shade-free zones every few hundred meters; integrate design with the landscape |

## Future Plan

- Improve LDR tracking accuracy and response time.
- Upgrade the structure with stronger, weather-resistant materials for long-term outdoor use.
- Add solar power to make the unit self-sufficient.
- Connect multiple units along a pathway to create a fully interactive smart walkway.

## License

Academic project — feel free to fork and adapt for educational purposes.

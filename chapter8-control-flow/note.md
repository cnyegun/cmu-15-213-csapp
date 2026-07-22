Processor executes instruction one after another

Called control flow

Two mechanism to alter control flow
- Branches and Jump
- Call and return
-> These react to changes in _program state_

Not enough for a useful system that react to changes in _system state_
- Data arrives through network
- Divides by zero
- Abort

ECF - *Exceptional control flow*

Event happens -> Control transfer from User code to Kernel code

#pragma once

#define BitSet(REG, BIT) (REG|(1<<BIT))
#define BitClr(REG, BIT) (REG&~(1<<BIT))
#define BitCpl(REG, BIT) (REG^(1<<BIT))
#define BitGet(REG, BIT) ((REG>>BIT)&1)
#define BitVal(REG, BIT, VAL) (if(VAL) BitSet(REG,BIT); else BitClr(REG,BIT);)
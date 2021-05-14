Explanation:

```
+                          // set the accumulator to one by incrementing (initialization)
 &1:0                      // set register 1 to value 0 (initialization)
     ¤               ←1    // define a target that can be jumped to; then, jump to the previously defined jump target
      n                    // print the accumulator and implicitly print the following space
        &0:@1              // set register 0 to register 1
             &1:a          // set register 1 to the value of the accumulator
                 #         // for as many times...
                  @0       //     ... as [value of register 0]...
                    +      //         ... increment the accumulator
```

I find it a bit hard to explain this, so here's a rough chart of the accumulator and the two registers used during execution which will hopefully remove any confusion:

```
acc   reg[0]    reg[1] |
---------------------- |
1     <uninit>  0      | initialize; print acc("1")
1     0         1      | set reg[0] to reg[1]; set reg[1] to acc
1     0         1      | add reg[0] to acc; jump back and print acc ("1")
1     1         1      | set reg[0] to reg[1]; set reg[1] to acc
2     1         1      | add reg[0] to acc; jump back and print acc ("1")
2     1         2      | set reg[0] to reg[1]; set reg[1] to acc
3     1         2      | add reg[0] to acc; jump back and print acc ("1")
3     2         3      | set reg[0] to reg[1]; set reg[1] to acc
5     2         3      | add reg[0] to acc; jump back and print acc ("1")
5     3         5      | set reg[0] to reg[1]; set reg[1] to acc
8     3         5      | add reg[0] to acc; jump back and print acc ("1")
``` 

sub    $0x18,%rsp    		# grow the stack by 24 bytes            
lea    0xc(%rsp),%rcx   # rcx = rsp + 12, trying to store a 4byte?
lea    0x8(%rsp),%rdx   # rdx = rsp + 8, 
mov    $0x4025cf,%esi   # (%esi) = "%d %d"
mov    $0x0,%eax        # rax = 0
call   0x400bf0 <__isoc99_sscanf@plt> # rax is 2 after input "2 4" and there's also 2 4 and (8) pushed to the stack(?)
cmp    $0x1,%eax   # if rax > 1        
jg     0x400f6a <phase_3+39>   # jump
call   0x40143a <explode_bomb>           
cmpl   $0x7,0x8(%rsp)                    
ja     0x400fad <phase_3+106>            
mov    0x8(%rsp),%eax          # move x to $eax          
jmp    *0x402470(,%rax,8)      #         
mov    $0xcf,%eax                        
jmp    0x400fbe <phase_3+123>            
mov    $0x2c3,%eax                       
jmp    0x400fbe <phase_3+123>            
mov    $0x100,%eax                       
jmp    0x400fbe <phase_3+123>            
mov    $0x185,%eax                       
jmp    0x400fbe <phase_3+123>            
mov    $0xce,%eax                        
jmp    0x400fbe <phase_3+123>            
mov    $0x2aa,%eax                       
jmp    0x400fbe <phase_3+123>            
mov    $0x147,%eax                       
jmp    0x400fbe <phase_3+123>            
call   0x40143a <explode_bomb>           
mov    $0x0,%eax                         
jmp    0x400fbe <phase_3+123>            
mov    $0x137,%eax                       
cmp    0xc(%rsp),%eax                    
je     0x400fc9 <phase_3+134>            
call   0x40143a <explode_bomb>           
add    $0x18,%rsp                        
ret                 


"x y"

x need to be smaller than 0x7
y look at the table value


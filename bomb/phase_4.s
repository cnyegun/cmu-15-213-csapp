
<+0>:     sub    $0x18,%rsp       # grow the stack 24 bytes                
<+4>:     lea    0xc(%rsp),%rcx   # rcx = rsp + 12                
<+9>:     lea    0x8(%rsp),%rdx   # rdx = rsp + 8                
<+14>:    mov    $0x4025cf,%esi   # esi = "%d %d"        
<+19>:    mov    $0x0,%eax        # eax = 0                
<+24>:    call   0x400bf0 <__isoc99_sscanf@plt>   
<+29>:    cmp    $0x2,%eax        #                 
<+32>:    jne    0x401035 <phase_4+41>            
<+34>:    cmpl   $0xe,0x8(%rsp)                   
<+39>:    jbe    0x40103a <phase_4+46>            
<+41>:    call   0x40143a <explode_bomb>          
<+46>:    mov    $0xe,%edx                        
<+51>:    mov    $0x0,%esi                        
<+56>:    mov    0x8(%rsp),%edi                   
<+60>:    call   0x400fce <func4>                 
<+65>:    test   %eax,%eax                        
<+67>:    jne    0x401058 <phase_4+76>            
<+69>:    cmpl   $0x0,0xc(%rsp)                   
<+74>:    je     0x40105d <phase_4+81>            
<+76>:    call   0x40143a <explode_bomb>          
<+81>:    add    $0x18,%rsp                       
<+85>:    ret      

; input format: "%d %d"
; x <= 14, y 

func4(x, 0, 14)
			x, y, z
<+0>: sub    $0x8,%rsp   ;grows the stack 8 bytes           
<+4>: mov    %edx,%eax   ;r = z           
<+6>: sub    %esi,%eax   ;r = z - y           
<+8>: mov    %eax,%ecx        
<+10> shr    $0x1f,%ecx             
<+13> add    %ecx,%eax   ;r += r >> 31           
<+15> sar    $1,%eax     ;r >>= 1           
<+17> lea    (%rax,%rsi,1),%ecx   ;tmp = r + y
<+20> cmp    %edi,%ecx   ;cmp (r + y) to x      
<+22> jle    0x400ff2 <func4+36> ;jump if (r + y) <= x  
<+24> lea    -0x1(%rcx),%edx ;   ;z = (r + y) - 1    
<+27> call   0x400fce <func4>    ;func(x, y, (r + y) - 1)  
<+32> add    %eax,%eax           ;eax += eax   
<+34> jmp    0x401007 <func4+57> ;
<+36> mov    $0x0,%eax              
<+41> cmp    %edi,%ecx              
<+43> jge    0x401007 <func4+57>    
<+45> lea    0x1(%rcx),%esi         
<+48> call   0x400fce <func4>       
<+53> lea    0x1(%rax,%rax,1),%eax  
<+57> add    $0x8,%rsp              
<+61> ret

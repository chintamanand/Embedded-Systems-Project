/**************************************************************************
 
 * Port lines used: Data1 to Data4 - P0.23 to P0.26
 * En - P0.28. RS - P0.27, RW - Ground
 * Connection : CND to CNAD. Short jumper JP16
 ***************************************************************************/

 #include <lpc17xx.h>

#define RS_CTRL  0x08000000  //P0.27
#define EN_CTRL  0x10000000  //P0.28
#define DT_CTRL  0x07800000  //P0.23 to P0.26 data lines

void scan(void);
void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);						   
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(unsigned char *);

unsigned char col,row,flag;
 unsigned long int i,var1,temp,temp3; // for keyboard interfacing
 unsigned long int temp1=0, temp2=0,count,num1,num2,res,first_dig,second_dig,sign_flag;
 unsigned char tempz[5],result[5];
 /*unsigned char Msg1[14] = {"WHOF"};
 unsigned char Msg2[15] = {"WHOOF"};*/
 
 

unsigned char seven_code[4][4]={{0x31,0x32,0x33,0x34}, {0x35,0x36,0x37,0x38}, {0x39,0x30,0x2B,0x2D}, {0x90,0x61,0x50,0x3D}};
 int main(void)
 {
	SystemInit();
	SystemCoreClockUpdate();
  
	 
	 LPC_GPIO2->FIODIRL=0x3C00;
	 
    lcd_init();				//initialise LCD
	delay_lcd(3200);

	temp1 = 0x80;			//1st message on LCD 1st line
	lcd_com();
	delay_lcd(800);
	//lcd_puts(Msg1);
		while(1)
		{

		 for(row = 0; row<4; row++)
		 {
			 if(row == 0)
				 temp = 0x00000400;
			 else if(row == 1)
					temp = 0x00000800;
			 else if(row == 2)
				 temp = 0x00001000;
			 else if(row == 3)
				 temp = 0x00002000;
			 LPC_GPIO2->FIOPIN = temp;
			 flag= 0;
			 scan();
			 if(flag == 1)
			 {
				 count++;
				 tempz[0]=seven_code[row][col];
				 
				 
				 
				 
				 
				 if(count==1)
				 {
					 if(tempz[0]>=0x30 && tempz[0]<=0x39)  //checking if first input is digit
							num1=tempz[0]-0x30;
					 else 
						{
						 count--;continue;
						}
					}
				 else if(count==2)
				 {
					 if(tempz[0]==0x2B)				//checking if second input is "+" or "-"
						 sign_flag=0;							//sign flag=0 for "+" ,signflag=1 for "-"
					 else if(tempz[0]==0x2D)
						 sign_flag=1;
				   else {count--;continue;} 
					}
				 else if(count==3) 					//checking if third input is digit
					 {
						 if(tempz[0]>=0x30 && tempz[0]<=0x39)
						 {
							 num2=tempz[0]-0x30;
							 if(sign_flag==0)	
									res=num1+num2;
							 else if(sign_flag==1)
							 {
								 if(num2>num1)
									res=num2-num1;
								 else res=num1-num2;
							 }
							
							 first_dig=res/10;
							 second_dig=res%10;
							 
							 
							 if(sign_flag==1)
							 {
								 if(num1>num2)
									 result[0]=first_dig+0x30; 
								 if(num1<num2) 
									 result[0]=0x2D;			// storing "-" sign as first dig of result
							 }
							 else result[0]=first_dig+0x30; 
											
							  
							 
							 
							 result[1]=second_dig+0x30;
						 }
						 else 
						 {count--;continue;}
						}
				 
				 
						
				 if(count!=4)
					 lcd_puts(tempz);
				 
						
				 if(count==4)
				 {
					 if(tempz[0]!=0x3D){count--;continue;}
					  
					  temp1=0xC0;				//Result in next line
					  lcd_com();
					 
						lcd_puts(tempz);	//displaying "=" sign
					  lcd_puts(result);	//displaying result
				 }
				 
							for(i=0;i<50000;i++);
							clear_ports();
			
							temp1=0x14;
							lcd_com();
							
							delay_lcd(800);
							break;
				 
				 
			 }
		 }
	 }
 }

 //lcd initialization
 void lcd_init()
 {
	/* Ports initialized as GPIO */
    LPC_PINCON->PINSEL1 &= 0xFC003FFF;  //P0.23 to P0.28

	/* Setting the directions as output */
    LPC_GPIO0->FIODIR |= DT_CTRL;	
	LPC_GPIO0->FIODIR |= RS_CTRL;	
	LPC_GPIO0->FIODIR |= EN_CTRL;	
        
    clear_ports();
	delay_lcd(3200);

	temp2 = (0x30<<19);
	wr_cn();	   
	delay_lcd(30000); 
		
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);	 
		
	temp2 = (0x30<<19);
	wr_cn();
	delay_lcd(30000);

	temp2 = (0x20<<19);
	wr_cn();
	delay_lcd(30000);

	temp1 = 0x28;
	lcd_com();
	delay_lcd(30000);
		
	temp1 = 0x0C;		
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x06;
	lcd_com();
	delay_lcd(800);
	
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
	
	temp1 = 0x80;
	lcd_com();
	delay_lcd(800);
    return;
 }
 
  void scan(void)
 {
	 temp3=LPC_GPIO1->FIOPIN;
	 temp3=temp3&0x07800000;
	 if(temp3!=0x0)
	 {
		 flag=1;
		 if(temp3==0x00800000)
			 col=0;
		 else if(temp3==0x01000000)
			 col=1;
		 else if(temp3==0x02000000)
			 col=2;
		 else if(temp3==0x04000000)
			 col=3;
	 }
 }

 void lcd_com(void)
 {
	temp2 = temp1 & 0xf0;//move data (26-8+1) times : 26 - HN place, 4 - Bits
	temp2 = temp2 << 19;//data lines from 23 to 26
	wr_cn();
	temp2 = temp1 & 0x0f; //26-4+1
	temp2 = temp2 << 23; 
	wr_cn();
	delay_lcd(1000);
    return;
 }

 // command nibble o/p routine
 void wr_cn(void)                        //write command reg
 { 	 
	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;		// Assign the value to the data lines    
    LPC_GPIO0->FIOCLR = RS_CTRL;		// clear bit RS
	LPC_GPIO0->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;		 		// EN =0
    return;
    
 }

 // data o/p routine which also outputs high nibble first
 // and lower nibble next
 void lcd_data(void)
 {             
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 19;
    wr_dn();
    temp2= temp1 & 0x0f;	
    temp2= temp2 << 23;
    wr_dn();
    delay_lcd(1000);	
    return;
 } 

 // data nibble o/p routine
 void wr_dn(void)
 {  	  
	clear_ports();

	LPC_GPIO0->FIOPIN = temp2;		// Assign the value to the data lines    
	LPC_GPIO0->FIOSET = RS_CTRL;	// set bit  RS
	LPC_GPIO0->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;	// EN =0
    return;
 }

 void delay_lcd(unsigned int r1)
 {
  	unsigned int r;
  	for(r=0;r<r1;r++);
    return;
 }

 void clr_disp(void)
 {
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
    return;
 }
 void clear_ports(void)
 {
    /* Clearing the lines at power on */
	LPC_GPIO0->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO0->FIOCLR = RS_CTRL;  //Clearing RS line
	LPC_GPIO0->FIOCLR = EN_CTRL; //Clearing Enable line
        
    return;
 }

 void lcd_puts(unsigned char *buf1)
 {
     unsigned int i=0;

    while(buf1[i]!='\0')
    {
        temp1 = buf1[i];
     	lcd_data();
		i++;
        if(i==16)
		{
           	temp1 = 0xc0;
			lcd_com();
		}
         
       }
    return;
 }

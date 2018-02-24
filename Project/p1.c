 #include <lpc17xx.h>
#include <stdio.h>
#include <math.h>
#define RS_CTRL  0x08000000  
#define EN_CTRL  0x10000000  
#define DT_CTRL  0x07800000  

void scan(void);
void lcd_init(void);
void wr_cn(void);
void clr_disp(void);
void delay_lcd(unsigned int);
void lcd_com(void);						   
void wr_dn(void);
void lcd_data(void);
void clear_ports(void);
void lcd_puts(char *);
 void calcu();
unsigned char col,row,flag;
char a[100];
unsigned long int i,var1,temp,temp3,x,c=0,op,d=0; // for keyboard interfacing
unsigned long int temp1=0, temp2=0,count=0,first_dig,second_dig,op_flag=0,k;
char tempz[5],num1[10]={0},num2[10]={0},result[10],b[100];
unsigned char seven_code[4][4]={{0x30,0x31,0x32,0x33}, {0x34,0x35,0x36,0x37}, {0x38,0x39,0x2e,0x2e}, {0x2e,0x2e,0xFE,0xFF}};
unsigned char op_code[4][4]={{0x2b,0x2d,0x2a,0x2f},{'%','t','c','s'},{'l','L','f','i'},{'p','S','C',0x3d}};
 int main(void)
 {
	SystemInit();
	SystemCoreClockUpdate();	 
	LPC_GPIO2->FIODIR=0x3C00; 
    lcd_init();				
	delay_lcd(3200);
	temp1 = 0x80;			
	lcd_com();
	delay_lcd(800);
	while(1)
		{
		for(row = 0; row<4; row++)
		{
			LPC_GPIO2->FIOPIN = 0x1<<(row+10);
			flag= 0;
			scan();	
			if(flag == 1)
			{	//	tempz[0]=count+0x30;
					//	lcd_puts(tempz);
				for(i=0;i<50000;i++);
				clear_ports();		
				count++;	
				//if(!x)
				tempz[0]=seven_code[row][col];
				if(count==1)
				 {
					 if((tempz[0]>=0x30 && tempz[0]<=0x39) ||(tempz[0]==(0x2e))) //checking if first input is digit
					 {	
					 		if(tempz[0]!=0x2e)
							{
								num1[c++]=tempz[0]-0x30;
								count--;
						  		lcd_puts(tempz);
						 		for(i=0;i<50000;i++);
								clear_ports();
							}
							else
							{
									num1[c++]='.';
									count--;
						  			lcd_puts(tempz);
						 			for(i=0;i<50000;i++);
									clear_ports();
							}
					}
						
					//		tempz[0]=count+0x30;
					//	lcd_puts(tempz);
					//		for(i=0;i<50000;i++);
					//		clear_ports();
						
							
				 }
			 	
				 else if(count==2)
				 {
					  
					 tempz[0]=op_code[row][col] ;
					  op=tempz[0];
					  if(op!=0x2b&&op!=0x2d&&op!=0x2a&&op!=0x2f&&op!='p'&&op!='%')
					  {
					  	op_flag=1;
					  	count=3;
					  }
					  
					 lcd_puts(tempz);

					 for(i=0;i<50000;i++);
							clear_ports();
					 //tempz[0]=count+0x30;
					//	lcd_puts(tempz);
					//		for(i=0;i<50000;i++);
					//		clear_ports();
				 }
				 else if(count==3) 					//checking if third input is digit
					 {
						if((tempz[0]>=0x30 && tempz[0]<=0x39) ||(tempz[0]==(0x2e)))
						 {
							if(tempz[0]!=0x2e)
							{
							num2[d++]=tempz[0]-0x30;
							count--;
							lcd_puts(tempz);
							 for(i=0;i<50000;i++);
							clear_ports();
							continue;
							}
								else
								{
									num2[d++]='.';
									count--;
						  			lcd_puts(tempz);
						 			for(i=0;i<50000;i++);
									clear_ports();
								}
						 }
					 }	 
				 else if(count==4)
				 	
					 {		
					 		tempz[0]=op_code[row][col]; 						
							 if(tempz[0]==0x3d)
							 {
							     calcu();	 							
								  temp1 = 0xc0;
							   	  lcd_com();
								  delay_lcd(800);
								  lcd_puts(tempz);
								 lcd_puts(result);							
							 }
							 
						 }
						 else if(count==5)
						 	{
								tempz[0]=seven_code[row][col];
								if(tempz[0]==0xFE)
									{
										clr_disp();	
										for(i=0;i<10;i++)
										{
											num1[i]='0';
										}
										
										for(c=0;c<k;c++)
										{	 if(result[c]!='.')
												num1[c]=(result[c]-0x30);
											else
												num1[c]='.';

										}
										
										c=k;
									
										lcd_puts(result);
										for(i=0;i<50000;i++);
										clear_ports();
							for(d=0;d<10;d++)
										{
										num2[d]=0x30-0x30;
										result[d]=0x30-0x30;
										}
											op_flag=0;
								  			 d=0;
											 count=1;
											
									}
									else
							 {
								 clr_disp();
									
										
										for(d=0;d<10;d++)
										{	num1[d]=0x30-0x30;
											num2[d]=0x30-0x30;
											result[d]=0x30-0x30;	
										}
										
									for(i=0;i<50000;i++);
									clear_ports();
	 
								op_flag=0;
								 c=0;
								 d=0;
								 count=0;
										
						   }
							}
						
					 }
				 
				 	
				 }
			 }
		 }
 

 
 void lcd_init()
 {
	
    LPC_PINCON->PINSEL1 &= 0xFC003FFF;  

	
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
	temp2 = temp1 & 0xf0;
	temp2 = temp2 << 19;
	wr_cn();
	temp2 = temp1 & 0x0f; 
	temp2 = temp2 << 23; 
	wr_cn();
	delay_lcd(1000);
    return;
 }

 void wr_cn(void)                        
 { 	clear_ports();
	LPC_GPIO0->FIOPIN = temp2;		
    LPC_GPIO0->FIOCLR = RS_CTRL;		
	LPC_GPIO0->FIOSET = EN_CTRL;   	
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;		 		
    return;
    
 }
 
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

 void wr_dn(void)
 {  	  
	clear_ports();

	LPC_GPIO0->FIOPIN = temp2;	   
	LPC_GPIO0->FIOSET = RS_CTRL;
	LPC_GPIO0->FIOSET = EN_CTRL;   
	delay_lcd(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
    return;
 }

 void delay_lcd(unsigned int r1)
 {
  	unsigned int r;
  	for(r=0;r<r1;r++){
			;
		}
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
	LPC_GPIO0->FIOCLR = DT_CTRL;
	LPC_GPIO0->FIOCLR = RS_CTRL;
	LPC_GPIO0->FIOCLR = EN_CTRL;
        
    return;
 }

 void lcd_puts(char *buf1)
 {
     unsigned int i=0;
    while(buf1[i]!='\0')
    {
        temp1 = buf1[i];
     	lcd_data();
		i++;    
       }
    return;
 }
void calcu()
 {
	 float res1=0,res2=0,resf,temp;
	 int l;
	
	 for(k=0;k<c;k++)
	 {		
		 if(num1[k]!='.')
			 res1=res1*10.0+(num1[k]);
		 else
		 {
			 
			 for(l=1;l+k<c;l++)
			 {
			 	 temp=(float)((num1[k+l]))/(10.0*l);
				 				

				 res1=res1+temp;
			 }
			 k=c;
		 }
	 }
		sprintf(b,"%.3f",res1)	 ;
	 lcd_puts(b);
										for(i=0;i<50000;i++);
										clear_ports();
	 if(op_flag!=1)
	 {
	 for(k=0;k<d;k++)
	 {	 	 
		 if(num2[k]!='.')
			 res2=res2*10.0+num2[k];
		 else
		 { 
			 for(l=1;l+k<d;l++)
			 {
			 
				 temp=((float)((num2[k+l])))/(10.0*l);
			
				 res2=res2+temp;
			 }
			 k=d;
		 }
	 
		}
	}
	

		   	k=0;

		
		if(op==0x2b)
		{
			resf=res1+res2;
		}
		else if(op==0x2d)
		{
			resf=res1-res2;
		}
		else if(op==0x2a)
		{
			resf=res1*res2;
		}
		else if(op==0x2f)
		{
			resf=res1/res2;
		}
		else if(op=='s')
		{
			res1=res1*3.14/180;
			resf=sin(res1);
		}
		else if(op=='c')
		{	res1=res1*3.14/180;
			resf=cos(res1);
		}
		else if(op=='t')
		{	res1=res1*3.14/180;
			resf=tan(res1);
		}
		else if(op=='p')
		{
			resf=pow(res1,res2);
		}
		else if(op=='f')
		{	   int p;
			resf=1;
			for(p=1;p<=res1;p++)
			{
			resf=resf*p;
			}
		}
		else if(op=='%')
		{
			resf=(int)res1%(int)res2;
		}
		else if(op=='l')
		{
			resf=log10(res1);
		}
		else if(op=='L')
		{
			resf=log(res1);
		}
		else if(op=='C')
		{
			resf=pow(res1,3);
		}
		else if(op=='S')
		{
			resf=pow(res1,2);
		}
		else if(op=='i')
		{
			resf=pow(res1,-1);
		}
				

		

		 op_flag=0;
	
		
		sprintf(result,"%.3f",resf)	 ;
		k=sizeof(result)/sizeof(result[0]);
		 /*while(resf!=0)
                    {
							 
                        result[k] = (resf%10) + 0x30;       //ascii conversion saath me
						tempz[0]=result[k];
						lcd_puts(tempz);
							for(i=0;i<50000;i++);
							clear_ports();
                        resf = resf/10 ;
                        k++;
                    }
		   */
	
		
	}

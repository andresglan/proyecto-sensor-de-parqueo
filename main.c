/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdlib.h>
#include <stdio.h>


uint16 	TimeDistMeas 	= 0,	TimeDistMeas1 	= 0;					// Value read from TimeDistMeas, eg HC-SRO4 PW returned, in 1 uS increments
float 	distmeas 		= 0.0,  distmeas1 		= 0.0;					// Value measured, uS / 148 = inches
char 	dispbuff[ 20 ],         dispbuff1[ 20 ];						// Display buffer for strings

volatile int caso=0,dato=0;
int i=0,n1=0,n2=0,n3=0;
char vec1[3]={11,11,11};

CY_ISR(ISR_KB){                         //Teclado Profesional       
    uint8 tecla, columna;
    tecla=Filas_Read();
    columna=Columnas_Read();
    tecla=tecla<<4;
    tecla=tecla|columna;
    LCD_ClearDisplay();
    switch(tecla){
        case 0b01110111: //tecla D
        
        LCD_Position(1,1);
        LCD_PrintString("Sensor a 10cm");
        
        caso=1;
        break;
        case 0b01111011: //tecla C
        
        LCD_Position(1,1);
        LCD_PrintString("Sensor a 25cm"); //check
        
        caso=2;
        break;
        case 0b01111101://tecla B
        
        LCD_Position(1,1);
        LCD_PrintString("Sensor a 50cm"); //check
        
        caso=3;
        break;
        case 0b01111110://Tecla A

        LCD_Position(1,1);
        LCD_PrintString("Sensor a 100cm"); //check
        caso=4;
        break;
        case 0b10110111://Tecla #
        
        LCD_Position(1,1);
        LCD_PrintString("Ingrese valor"); //check
        caso=5;
        break;
        case 0b10111011://tecla 9
        
        if(caso==5){
            
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("9");
                    vec1[i]=9;
                    break;
                }
            }
        }
       
        break;
        case 0b10111101://tecla 6
        
        if(caso==5){
            
            
            for(i=0;i<=2;i++){
                
                CyDelay(500);
                if(vec1[i]==11){
                    vec1[i]=6;
                    LCD_Position(1,1);
                    LCD_PrintString("6");
                    break;
                }
            }
        }
        break;
        case 0b10111110://tecla 3
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("3");
                    vec1[i]=3;
                    break;
                }
            }
        }
        break;
        case 0b11010111://tecla 0
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("0");
                    vec1[i]=0;
                    break;
                }
            }
        }
        break;
        case 0b11011011://tecla 8
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("8");
                    vec1[i]=8;
                    break;
                }
            }
        }
        break;
        case 0b11011101://tecla 5
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("5");
                    vec1[i]=5;
                    break;
                }
            }
        }
        break;
        case 0b11011110://tecla 2
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("2");
                    vec1[i]=2;
                    break;
                }
            }
        }
        break;
        case 0b11100111://Tecla * enter
        if(caso==5){
            if(vec1[0]!=11){
                n1=vec1[0];
                if(vec1[1]!=11){
                    n1=10*vec1[0];
                    n2=vec1[1]; 
                    if(vec1[2]!=11){
                        n1=100*vec1[0];
                        n2=10*vec1[1];
                        n3=vec1[2];
                    
                    }
                }
            }
            dato=n1+n2+n3;
            if(dato>150||dato<13){
                LCD_Position(0,0);
                LCD_PrintString("Valor erroneo");
                CyDelay(500);
                
                LCD_Position(1,0);
                LCD_PrintString("Intente de nuevo");
                dato=0;
                
            }else{
                caso=5;
                LCD_ClearDisplay();
                LCD_Position(0,0);
                LCD_PrintString("Valor Ingresado");
            }
            
            LCD_Position(1,1);
            LCD_PrintNumber(dato);
            n1=0;n2=0;n3=0;
            for(i=0;i<=2;i++){
                vec1[i]=11;
            }
        }
        break;
        case 0b11101011://tecla 7
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("7");
                    vec1[i]=7;
                    break;
                    
                }
            }
        }
        break;
        case 0b11101101://tecla 4
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("4");
                    vec1[i]=4;
                    break;
                }
            }
        }
        break;
        case 0b11101110://tecla 1
        if(caso==5){
            for(i=0;i<=2;i++){
                if(vec1[i]==11){
                    LCD_Position(1,1);
                    LCD_PrintString("1");
                    vec1[i]=1;
                    break;
                }
            }
        }
        break;
        
    }
    while(Filas_Read()!=0b1111);
    CyDelay(1500);
    i=0;
    LCD_ClearDisplay();
    Filas_ClearInterrupt();
    
}


int main( void ) {
	
							// for index variable
	ISR_KB_StartEx(ISR_KB);
    CyGlobalIntEnable; 							// Uncomment this line to enable global interrupts.
                              // Initialises UART

	TimeDistMeas_Start( );  
    TimeDistMeas_1_Start( );  
                                                // Start up the distance measuring timer, basically ,measure PW of pulse HC-SRO4 generates
	LCD_Start( );								// Start LCD module
    
    LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "Seleccione modo:" );
            
    LCD_Position( 1, 1); 
            
            LCD_PrintString( "A B C D #:Pers" );
    
    uint8 d1,d2;
	
    for(;;) {

	    Columnas_Write(0b1110);
        CyDelayUs(500);
        Columnas_Write(0b1101);
        CyDelayUs(500);
        Columnas_Write(0b1011);
        CyDelayUs(500);
        Columnas_Write(0b0111);
        CyDelayUs(500);
						// Cursor to Row 0, Col 0

		while( echo_Read( ) == 0) { 					// HC-SRO4 ready for a trigger, to start new measurement cycle ?
			
			Triggen_Write( 1 ); 								// Trigger the HC-SRO4 to issue the 10 uS start pulse, and reset TimeDistMeas
			CyDelayUs( 10 );									// Trigger high for 10 uS
			Triggen_Write( 0 );									// Remove trigger and reset from TimeDistMeas
			CyDelay( 1 );										// Delay 1 mS to see if HC-SRO4 started a measurement, if not issue another trigger to HC-SRO4
			
		}
        while(echo_1_Read()==0) { 					// HC-SRO4 ready for a trigger, to start new measurement cycle ?
			
			Triggen1_Write( 1 ); 								// Trigger the HC-SRO4 to issue the 10 uS start pulse, and reset TimeDistMeas
			CyDelayUs( 10 );									// Trigger high for 10 uS
			Triggen1_Write( 0 );									// Remove trigger and reset from TimeDistMeas
			CyDelay( 1 );										// Delay 1 mS to see if HC-SRO4 started a measurement, if not issue another trigger to HC-SRO4
			
		}
        
		while( echo_Read( ) == 1 ) { };	
        while( echo_1_Read()==1 ) { };      // Wait until HC-SRO4 finishes measurement cycle

		TimeDistMeas = 4294967296 - TimeDistMeas_ReadCounter( );		// Get timer value, PW in uS, of HC-SRO4
		distmeas = (float) TimeDistMeas / 56;				// Compute distance measured
		
        TimeDistMeas1 = 4294967296 - TimeDistMeas_1_ReadCounter( );		// Get timer value, PW in uS, of HC-SRO4
		distmeas1 = (float) TimeDistMeas1 / 56;				// Compute distance measured
        
		sprintf( dispbuff, "%.1f", distmeas );					// Convert distmeas to a string to print on LCD
		sprintf( dispbuff1, "%.1f", distmeas1 );
        
        
        
        switch(caso){
            case 1:
            d1=distmeas;
            d2=distmeas1;
        
            LCD_DrawHorizontalBG(0,11,15,d1); 
            LCD_DrawHorizontalBG(1,11,15,d2);
            LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "R1:" );
            LCD_Position( 1, 0 );									// Position cursor
    	
            LCD_PrintString( "R2:" );
            
            
            LCD_Position( 0, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff );
            
            LCD_Position( 1, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff1 );
      
            
                if(distmeas<=13 || distmeas1<=13){
                
                    buzzer_Write(1);
                    
                }else{
                
                    buzzer_Write(0);
                }
            
            break;
            case 2:
            d1=distmeas/2;
            d2=distmeas1/2;

            LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "R1:" );
            LCD_Position( 1, 0 );									// Position cursor
    	
            LCD_PrintString( "R2:" );
            
            
            LCD_Position( 0, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff );
            
            LCD_Position( 1, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff1 );    
                
            LCD_DrawHorizontalBG(0,11,15,d1); 
            LCD_DrawHorizontalBG(1,11,15,d2);
                if(distmeas<=25 || distmeas1<=25){
                
                    buzzer_Write(1);
                    
                }else{
                
                    buzzer_Write(0);
                }
            break;
            case 3:
            d1=distmeas/4;
            d2=distmeas1/4;
                
            LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "R1:" );
            LCD_Position( 1, 0 );									// Position cursor
    	
            LCD_PrintString( "R2:" );
            
            
            LCD_Position( 0, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff );
            
            LCD_Position( 1, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff1 );    
        
            LCD_DrawHorizontalBG(0,11,15,d1); 
            LCD_DrawHorizontalBG(1,11,15,d2);
                if(distmeas<=50 || distmeas1<=50){
                
                    buzzer_Write(1);
                    
                }else{
                
                    buzzer_Write(0);
                }
            break;
            case 4:
            d1=distmeas/8;
            d2=distmeas1/8;
                
            LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "R1:" );
            LCD_Position( 1, 0 );									// Position cursor
    	
            LCD_PrintString( "R2:" );
            
            
            LCD_Position( 0, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff );
            
            LCD_Position( 1, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff1 );    
        
            LCD_DrawHorizontalBG(0,11,15,d1); 
            LCD_DrawHorizontalBG(1,11,15,d2);
                if(distmeas<=100 || distmeas1<=100){
                
                    buzzer_Write(1);
                    
                }else{
                
                    buzzer_Write(0);
                }
            break;
            case 5:
                LCD_Position( 0, 0 );									// Position cursor
	
            LCD_PrintString( "R1:" );
            LCD_Position( 1, 0 );									// Position cursor
    	
            LCD_PrintString( "R2:" );
            
            
            LCD_Position( 0, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff );
            
            LCD_Position( 1, 3 );									// Position cursor
    	
            LCD_PrintString( dispbuff1 );
                
                if(dato<=15)
                {
                    d1=distmeas;
                    d2=distmeas1;
                }else{
                    if(dato<=25){
                        d1=distmeas/2;
                        d2=distmeas1/2;
                
                    }else{
                        if(dato<=50){
                            d1=distmeas/4;
                            d2=distmeas1/4;
                        
                        }else{
                            if(dato<=100){
                                d1=distmeas/8;
                                d2=distmeas1/8;
                            
                            }else{
                                d1=distmeas/12;
                                d2=distmeas1/12;
                            
                            }
                            
                        }
                    
                    
                    }
                
                
                }
        
            LCD_DrawHorizontalBG(0,11,15,d1); 
            LCD_DrawHorizontalBG(1,11,15,d2);
                if(distmeas<=dato || distmeas1<=dato){
                                       
                    buzzer_Write(1);
                                
                }else{
                
                    buzzer_Write(0);
                }
            break;
            
        
        
        }
        
        CyDelay(100);							// Wait 100 mS before triggering the HC-SRO4 module again	

	}
}

/* [] END OF FILE */



#define SSD1306_MEMORYMODE 0x20   
/*
first byte 20
second byte A[1:0]

A[1:0] = 00b, Horizontal Addressing Mode
A[1:0] = 01b, Vertical Addressing Mode
A[1:0] = 10b, Page Addressing Mode (RESET)
A[1:0] = 11b, Invalid
*/        
#define SSD1306_COLUMNADDR 0x21    
/*
21
A[6:0]
B[6:0]

Setup column start and end address
A[6:0] : Column start address, range : 0-127d,
(RESET=0d)
B[6:0]: Column end address, range : 0-127d,
(RESET =127d)
Note
(1)
This command is only for horizontal or vertical
addressing mode.
*/     
#define SSD1306_PAGEADDR 0x22            
#define SSD1306_SETCONTRAST 0x81         
#define SSD1306_CHARGEPUMP 0x8D          
#define SSD1306_SEGREMAP 0xA0            
#define SSD1306_DISPLAYALLON_RESUME 0xA4 
#define SSD1306_DISPLAYALLON 0xA5        
#define SSD1306_NORMALDISPLAY 0xA6       
#define SSD1306_INVERTDISPLAY 0xA7       
#define SSD1306_SETMULTIPLEX 0xA8        
#define SSD1306_DISPLAYOFF 0xAE          
#define SSD1306_DISPLAYON 0xAF           
#define SSD1306_COMSCANINC 0xC0          
#define SSD1306_COMSCANDEC 0xC8          
#define SSD1306_SETDISPLAYOFFSET 0xD3    
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5  
#define SSD1306_SETPRECHARGE 0xD9        
#define SSD1306_SETCOMPINS 0xDA          
#define SSD1306_SETVCOMDETECT 0xDB       

#define SSD1306_SETLOWCOLUMN 0x00  ///< Not currently used
#define SSD1306_SETHIGHCOLUMN 0x10 ///< Not currently used
#define SSD1306_SETSTARTLINE 0x40  

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26              ///< Init rt scroll
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27               ///< Init left scroll
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29 ///< Init diag scroll
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A  ///< Init diag scroll
#define SSD1306_DEACTIVATE_SCROLL 0x2E                    ///< Stop scroll
#define SSD1306_ACTIVATE_SCROLL 0x2F                      ///< Start scroll
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3             ///< Set scroll range
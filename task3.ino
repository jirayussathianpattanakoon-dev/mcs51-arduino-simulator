unsigned short In_Data_Mem[256];   // internal data memory size 256 byte
unsigned short Ex_Data_Mem[5120];  // External data memory size 5 Kbyte
//unsigned short Prog_Mem[1024];   // Program Memory 1 K byte

unsigned short Reg_opcode;    // Command Register
unsigned int   Reg_PC;        // Program Counter Register 16 bit
unsigned short Reg_cash[2];   // Cash Register 2 byte
unsigned short Reg_PSW = 0b00010000;  // 0-bit parity
                                      // 1-bit  NA
                                      // 2-bit  OV
                                      // 3-bit  RS0
                                      // 4-bit  RS1
                                      //        RS1|RS0
                                      //          0  0       = Register Bank 0    
                                      //          0  1       = Register Bank 1    
                                      //          1  0       = Register Bank 2     
                                      //          1  1       = Register Bank 3           
                                      // 5-bit  F0
                                      // 6-bit  AC
                                      // 7-bit  CY
unsigned int   Reg_DPTR;        // DPTR Register 16 bit
unsigned short Reg_A;           // Accumulater Register 8 bit

unsigned short Stack_Mem[]={0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00
                            };
unsigned short Reg_SP =0x00;

bool   flag_opcode_ena;        // allow to read program memory

unsigned short current_state, next_state;

unsigned short Prog_Mem[] = {      // Program Memory 1 K byte
// set 1
0x7F, 0x08, 0x7E, 0x00, 0x90, 0x13, 0x88, 0xE0, 0x12, 0x00, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0-19
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 20-39
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 40-59
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60-79
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80-99
// set 2
0x7B, 0x80, 0x7A, 0x00, 0x22, 0xFE, 0xDB, 0xFA, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100-119
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 3
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 4
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 5
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 6
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 7
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 8
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 9
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// set 10
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00
};

unsigned short Program_Mem(unsigned int Address){     
     return Prog_Mem[Address];
} 

void Internal_Data_Mem(unsigned int Address, unsigned short Data_in, unsigned short Data_out, bool RW){
     // RW = 1 Write
     //    = 0 Read
      if (RW){
        // Write Data into Internal Data Memory
           In_Data_Mem[Address]=Data_in;
      }else{
        // Read Data from Internal Data Memory
           Data_out = In_Data_Mem[Address];
      }
}

void External_Data_Mem(unsigned int Address, unsigned short Data_in, unsigned short Data_out, bool RW){
     // RW = 1 Write
     //    = 0 Read
      if (RW){
        // Write Data into Internal Data Memory
           Ex_Data_Mem[Address]=Data_in;
      }else{
        // Read Data from Internal Data Memory
           Data_out = Ex_Data_Mem[Address];
      }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  current_state  = 0;         // initial current state
  next_state     = 0;        // initial next state
  Reg_opcode     = 0x00;
  Reg_PC         = 0x0008;   // Reset Program Counter Register
  flag_opcode_ena  = true;   // allow to read program memory
  Reg_DPTR       = 0x0000;   // Reset DPTR Register
  Reg_A          = 0x00;     // Reset A Register

  Ex_Data_Mem[0x1388] = 0xAA;
  
  Serial.println("Computer Architecture V1.0 on ESP 32"); 
  Serial.println("- Architecture"); 
  Serial.println("- MCS-51 Instruction Set"); 
  Serial.println("- Hardware ESP32"); 
}

void Decode_opcode(unsigned short opcode){
unsigned short n_byte=0x00;     
     switch (opcode){
        case 0x00:
                  n_byte = 1;
                  Serial.println(" - NOP");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);                
                  break;
        case 0x01:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x02:
                  n_byte = 3;
                  if (flag_opcode_ena){
                      Reg_cash[0] = Program_Mem(Reg_PC+1); // High Byte (A15-A8)
                      Reg_cash[1] = Program_Mem(Reg_PC+2); // Low Byte (A7-A0)
                  }
                  Serial.println(" - LJMP code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] (High) = "); Serial.println(Reg_cash[0],HEX);
                  Serial.print(" - Reg_cash[1] (Low) = "); Serial.println(Reg_cash[1],HEX);
                  break;
        case 0x03:
                  n_byte = 1;
                  Serial.println(" - RR A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x04:
                  n_byte = 1;
                  Serial.println(" - INC A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x05:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - INC data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x06:
                  n_byte = 1;
                  Serial.println(" - INC @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x07:
                  n_byte = 1;
                  Serial.println(" - INC @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x08:
                  n_byte = 1;
                  Serial.println(" - INC R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x09:
                  n_byte = 1;
                  Serial.println(" - INC R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0A:
                  n_byte = 1;
                  Serial.println(" - INC R2");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0B:
                  n_byte = 1;
                  Serial.println(" - INC R3");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0C:
                  n_byte = 1;
                  Serial.println(" - INC R4");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0D:
                  n_byte = 1;
                  Serial.println(" - INC R5");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0E:
                  n_byte = 1;
                  Serial.println(" - INC R6");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x0F:
                  n_byte = 1;
                  Serial.println(" - INC R7");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x10:
                  n_byte = 3;
                  if (flag_opcode_ena){
                      Reg_cash[0] = Program_Mem(Reg_PC+1);
                      Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - JBC bit, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x11:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x12:
                  n_byte = 3;
                  if (flag_opcode_ena){
                    Reg_cash[0] = Program_Mem(Reg_PC+1);
                    Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - LCALL CodeAddr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte); 
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1],HEX);                
                  break;
        case 0x13:
                  n_byte = 1;
                  Serial.println(" - RRC A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x14:
                  n_byte = 1;
                  Serial.println(" - DEC A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x15:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DEC data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x16:
                  n_byte = 1;
                  Serial.println(" - DEC @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x17:
                  n_byte = 1;
                  Serial.println(" - DEC @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x18:
                  n_byte = 1;
                  Serial.println(" - DEC R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x19:
                  n_byte = 1;
                  Serial.println(" - DEC R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1A:
                  n_byte = 1;
                  Serial.println(" - DEC R2");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1B:
                  n_byte = 1;
                  Serial.println(" - DEC R3");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1C:
                  n_byte = 1;
                  Serial.println(" - DEC R4");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1D:
                  n_byte = 1;
                  Serial.println(" - DEC R5");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1E:
                  n_byte = 1;
                  Serial.println(" - DEC R6");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x1F:
                  n_byte = 1;
                  Serial.println(" - DEC R7");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x20:
                  n_byte = 3;
                  if (flag_opcode_ena){
                      Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                      Reg_cash[1] = Program_Mem(Reg_PC+2); // Relative Offset
                  }
                  Serial.println(" - JB bit, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x21:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;                  
        case 0x22:
                  n_byte = 1;
                  Serial.println(" - RET");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte); 
                //  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                //  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1],HEX);                
                  break;
        case 0x23:
                  n_byte = 1;
                  Serial.println(" - RL A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x24:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ADD A,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x25:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ADD A,data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x26:
                  n_byte = 1;
                  Serial.println(" - ADD A,@R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x27:
                  n_byte = 1;
                  Serial.println(" - ADD A,@R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x28:
                  n_byte = 1;
                  Serial.println(" - ADD A,R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x29:
                  n_byte = 1;
                  Serial.println(" - ADD A,R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2A:
                  n_byte = 1;
                  Serial.println(" - ADD A,R2");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2B:
                  n_byte = 1;
                  Serial.println(" - ADD A,R3");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2C:
                  n_byte = 1;
                  Serial.println(" - ADD A,R4");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2D:
                  n_byte = 1;
                  Serial.println(" - ADD A,R5");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2E:
                  n_byte = 1;
                  Serial.println(" - ADD A,R6");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x2F:
                  n_byte = 1;
                  Serial.println(" - ADD A,R7");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x30:
                  n_byte = 3;
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1);
                        Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - JNB bit, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Bit Addr = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Rel Offset = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x31:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x32:
                  n_byte = 1;
                  Serial.println(" - RETI");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
                        case 0x33:
                  n_byte = 1;
                  Serial.println(" - RLC A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x34:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ADDC A,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x35:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ADDC A,data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x36:
                  n_byte = 1;
                  Serial.println(" - ADDC A,@R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x37:
                  n_byte = 1;
                  Serial.println(" - ADDC A,@R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x38:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x39:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3A:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R2");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3B:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R3");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3C:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R4");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3D:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R5");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3E:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R6");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x3F:
                  n_byte = 1;
                  Serial.println(" - ADDC A,R7");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x40:
                  n_byte = 2; // คำสั่ง 2 Byte (Opcode + Offset)
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // เก็บค่า Relative Offset
                  Serial.println(" - JC rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x41:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x42:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ORL data_addr, A"); // เอา A ไป OR ใส่ Memory
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x43:
                  n_byte = 3;
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1); // Address ปลายทาง
                        Reg_cash[1] = Program_Mem(Reg_PC+2); // ค่าคงที่ที่จะเอาไป OR
                  }
                  Serial.println(" - ORL data_addr, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x44:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ORL A, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x45:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ORL A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x46:
                  n_byte = 1;
                  Serial.println(" - ORL A, @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x47:
                  n_byte = 1;
                  Serial.println(" - ORL A, @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x48:
                  n_byte = 1;
                  Serial.println(" - ORL A, R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x49:
                  n_byte = 1;
                  Serial.println(" - ORL A, R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4A:
                  n_byte = 1;
                  Serial.println(" - ORL A, R2");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4B:
                  n_byte = 1;
                  Serial.println(" - ORL A, R3");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4C:
                  n_byte = 1;
                  Serial.println(" - ORL A, R4");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4D:
                  n_byte = 1;
                  Serial.println(" - ORL A, R5");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4E:
                  n_byte = 1;
                  Serial.println(" - ORL A, R6");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x4F:
                  n_byte = 1;
                  Serial.println(" - ORL A, R7");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x50:
                  n_byte = 2; 
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - JNC rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x51:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x52:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ANL data_addr, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x53:
                  n_byte = 3;
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1);
                        Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - ANL data_addr, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x54:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ANL A, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x55:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ANL A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x56: n_byte = 1; Serial.println(" - ANL A, @R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x57: n_byte = 1; Serial.println(" - ANL A, @R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x58: n_byte = 1; Serial.println(" - ANL A, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x59: n_byte = 1; Serial.println(" - ANL A, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5A: n_byte = 1; Serial.println(" - ANL A, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5B: n_byte = 1; Serial.println(" - ANL A, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5C: n_byte = 1; Serial.println(" - ANL A, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5D: n_byte = 1; Serial.println(" - ANL A, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5E: n_byte = 1; Serial.println(" - ANL A, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x5F: n_byte = 1; Serial.println(" - ANL A, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x60:
                  n_byte = 2; 
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - JZ rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); 
                  break;
        case 0x61:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x62:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - XRL data_addr, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x63:
                  n_byte = 3; // 3 Bytes !!!
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1); // Address
                        Reg_cash[1] = Program_Mem(Reg_PC+2); // Data
                  }
                  Serial.println(" - XRL data_addr, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x64:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - XRL A, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x65:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - XRL A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x66: n_byte = 1; Serial.println(" - XRL A, @R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x67: n_byte = 1; Serial.println(" - XRL A, @R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x68: n_byte = 1; Serial.println(" - XRL A, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x69: n_byte = 1; Serial.println(" - XRL A, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6A: n_byte = 1; Serial.println(" - XRL A, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6B: n_byte = 1; Serial.println(" - XRL A, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6C: n_byte = 1; Serial.println(" - XRL A, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6D: n_byte = 1; Serial.println(" - XRL A, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6E: n_byte = 1; Serial.println(" - XRL A, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x6F: n_byte = 1; Serial.println(" - XRL A, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x70:
                  n_byte = 2; 
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - JNZ code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); 
                  break;
        case 0x71:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x72:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                  Serial.println(" - ORL C, bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x73:
                  n_byte = 1;
                  Serial.println(" - JMP @A+DPTR");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x74:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data
                  Serial.println(" - MOV A, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x75:
                  n_byte = 3; // 3 Bytes !!!
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1); // Address ปลายทาง
                        Reg_cash[1] = Program_Mem(Reg_PC+2); // ค่า Data ที่จะใส่
                  }
                  Serial.println(" - MOV data_addr, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x76:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data
                  Serial.println(" - MOV @R0, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x77:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data
                  Serial.println(" - MOV @R1, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x78:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R0,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x79:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R1,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7A:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R2,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7B:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R3,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7C:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R4,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7D:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R5,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7E:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R6,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x7F:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R7,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  break;
        case 0x80:
                  n_byte = 2; // 2 Byte (Opcode + Offset)
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่านค่า Offset
                  Serial.println(" - SJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x81:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x82:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                  Serial.println(" - ANL C, bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x83:
                  n_byte = 1;
                  Serial.println(" - MOVC A, @A+PC");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x84:
                  n_byte = 1;
                  Serial.println(" - DIV AB");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x85:
                  n_byte = 3; 
                  if (flag_opcode_ena){
                        Reg_cash[0] = Program_Mem(Reg_PC+1); // Source Address
                        Reg_cash[1] = Program_Mem(Reg_PC+2); // Dest Address
                  }
                  Serial.println(" - MOV data_addr, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0x86:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV data_addr, @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x87:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV data_addr, @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x88: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x89: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8A: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8B: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8C: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8D: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8E: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x8F: n_byte = 2; if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); Serial.println(" - MOV data_addr, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX); break;
        case 0x90:
                  n_byte = 3;
                  if (flag_opcode_ena){
                    Reg_cash[0] = Program_Mem(Reg_PC+1);
                    Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - MOV DPTR,#data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0],HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1],HEX);
                  break;
        case 0x91:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x92:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Bit Address
                  Serial.println(" - MOV bit, C");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x93:
                  n_byte = 1;
                  Serial.println(" - MOVC A, @A+DPTR");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0x94:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - SUBB A, #data");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x95:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - SUBB A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0x96: n_byte = 1; Serial.println(" - SUBB A, @R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x97: n_byte = 1; Serial.println(" - SUBB A, @R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x98: n_byte = 1; Serial.println(" - SUBB A, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x99: n_byte = 1; Serial.println(" - SUBB A, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9A: n_byte = 1; Serial.println(" - SUBB A, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9B: n_byte = 1; Serial.println(" - SUBB A, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9C: n_byte = 1; Serial.println(" - SUBB A, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9D: n_byte = 1; Serial.println(" - SUBB A, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9E: n_byte = 1; Serial.println(" - SUBB A, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0x9F: n_byte = 1; Serial.println(" - SUBB A, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xA0:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                  Serial.println(" - ORL C, /bit"); // สังเกตเครื่องหมาย / (Inverse)
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA2:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                  Serial.println(" - MOV C, bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA3:
                  n_byte = 1;
                  Serial.println(" - INC DPTR");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xA4:
                  n_byte = 1;
                  Serial.println(" - MUL AB");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xA5:
                  n_byte = 1;
                  Serial.println(" - Reserved (0xA5) - treated as NOP");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xA6:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV @R0, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA7:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV @R1, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA8:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R0, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xA9:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R1, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAA:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R2, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAB:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R3, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAC:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R4, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAD:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R5, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAE:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R6, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xAF:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOV R7, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xB0:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Bit Address
                  Serial.println(" - ANL C, /bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xB1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xB2:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Bit Address
                  Serial.println(" - CPL bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xB3:
                  n_byte = 1;
                  Serial.println(" - CPL C");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xB4:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data (#data)
                  Reg_cash[1] = Program_Mem(Reg_PC+2); // Relative Offset (rel)
                  }
                  Serial.println(" - CJNE A, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xB5:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1); // Direct Address (data_addr)
                  Reg_cash[1] = Program_Mem(Reg_PC+2); // Relative Offset (rel)
                  }
                  Serial.println(" - CJNE A, data_addr, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
            case 0xB6:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data
                  Reg_cash[1] = Program_Mem(Reg_PC+2); // Relative Offset
                  }
                  Serial.println(" - CJNE @R0, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xB7:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1); // Immediate Data
                  Reg_cash[1] = Program_Mem(Reg_PC+2); // Relative Offset
                  }
                  Serial.println(" - CJNE @R1, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xB8:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R0, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xB9:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R1, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBA:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R2, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBB:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R3, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBC:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R4, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBD:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R5, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBE:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R6, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xBF:
                  n_byte = 3;
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Reg_cash[1] = Program_Mem(Reg_PC+2);
                  }
                  Serial.println(" - CJNE R7, #data, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xC0:
                  n_byte = 2; // 2 Byte (Opcode + Direct Address)
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Address ที่จะ PUSH
                  Serial.println(" - PUSH data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xC1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xC2:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Bit Address
                  Serial.println(" - CLR bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xC3:
                  n_byte = 1;
                  Serial.println(" - CLR C");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xC4:
                  n_byte = 1;
                  Serial.println(" - SWAP A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xC5:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Direct Address
                  Serial.println(" - XCH A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xC6: n_byte = 1; Serial.println(" - XCH A, @R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xC7: n_byte = 1; Serial.println(" - XCH A, @R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xC8: n_byte = 1; Serial.println(" - XCH A, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xC9: n_byte = 1; Serial.println(" - XCH A, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCA: n_byte = 1; Serial.println(" - XCH A, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCB: n_byte = 1; Serial.println(" - XCH A, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCC: n_byte = 1; Serial.println(" - XCH A, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCD: n_byte = 1; Serial.println(" - XCH A, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCE: n_byte = 1; Serial.println(" - XCH A, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xCF: n_byte = 1; Serial.println(" - XCH A, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xD0:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Direct Address ที่จะรับค่า
                  Serial.println(" - POP data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xD1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xD2:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Bit Address
                  Serial.println(" - SETB bit");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xD3:
                  n_byte = 1;
                  Serial.println(" - SETB C");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xD4:
                  n_byte = 1;
                  Serial.println(" - DA A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xD5:
                  n_byte = 3; // 3 Byte (Opcode + Direct Addr + Rel Offset)
                  if (flag_opcode_ena) {
                  Reg_cash[0] = Program_Mem(Reg_PC+1); // Address ที่จะลดค่า
                  Reg_cash[1] = Program_Mem(Reg_PC+2); // Offset ที่จะกระโดด
                  }
                  Serial.println(" - DJNZ data_addr, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  Serial.print(" - Reg_cash[1] = "); Serial.println(Reg_cash[1], HEX);
                  break;
        case 0xD6:
                  n_byte = 1;
                  Serial.println(" - XCHD A, @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xD7:
                  n_byte = 1;
                  Serial.println(" - XCHD A, @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xD8:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // อ่าน Offset
                  Serial.println(" - DJNZ R0, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xD9:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R1, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDA:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R2, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDB:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R3, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDC:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R4, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDD:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R5, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDE:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R6, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xDF:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - DJNZ R7, rel");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xE0:
                  n_byte = 1;
                  //if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - MOVX A,@DPTR");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);                 
                  break;
        case 0xE1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - AJMP code addr ");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xE2:
                  n_byte = 1;
                  Serial.println(" - MOVX A, @R0");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xE3:
                  n_byte = 1;
                  Serial.println(" - MOVX A, @R1");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xE4:
                  n_byte = 1;
                  Serial.println(" - CLR A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xE5:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Direct Address
                  Serial.println(" - MOV A, data_addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xE6: n_byte = 1; Serial.println(" - MOV A, @R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xE7: n_byte = 1; Serial.println(" - MOV A, @R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xE8: n_byte = 1; Serial.println(" - MOV A, R0"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xE9: n_byte = 1; Serial.println(" - MOV A, R1"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xEA: n_byte = 1; Serial.println(" - MOV A, R2"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xEB: n_byte = 1; Serial.println(" - MOV A, R3"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xEC: n_byte = 1; Serial.println(" - MOV A, R4"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xED: n_byte = 1; Serial.println(" - MOV A, R5"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xEE: n_byte = 1; Serial.println(" - MOV A, R6"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xEF: n_byte = 1; Serial.println(" - MOV A, R7"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xF0:
                  n_byte = 1;
                  Serial.println(" - MOVX @DPTR, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xF1:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1);
                  Serial.println(" - ACALL code addr");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xF2:
                  n_byte = 1;
                  Serial.println(" - MOVX @R0, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xF3:
                  n_byte = 1;
                  Serial.println(" - MOVX @R1, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xF4:
                  n_byte = 1;
                  Serial.println(" - CPL A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  break;
        case 0xF5:
                  n_byte = 2;
                  if (flag_opcode_ena) Reg_cash[0] = Program_Mem(Reg_PC+1); // Direct Address
                  Serial.println(" - MOV data_addr, A");
                  Serial.print(" - opcode byte = "); Serial.println(n_byte);
                  Serial.print(" - Reg_cash[0] = "); Serial.println(Reg_cash[0], HEX);
                  break;
        case 0xF6: n_byte = 1; Serial.println(" - MOV @R0, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xF7: n_byte = 1; Serial.println(" - MOV @R1, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xF8: n_byte = 1; Serial.println(" - MOV R0, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xF9: n_byte = 1; Serial.println(" - MOV R1, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFA: n_byte = 1; Serial.println(" - MOV R2, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFB: n_byte = 1; Serial.println(" - MOV R3, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFC: n_byte = 1; Serial.println(" - MOV R4, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFD: n_byte = 1; Serial.println(" - MOV R5, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFE: n_byte = 1; Serial.println(" - MOV R6, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;
        case 0xFF: n_byte = 1; Serial.println(" - MOV R7, A"); Serial.print(" - opcode byte = "); Serial.println(n_byte); break;

        default:
                  break;
    }
    //unsigned short Reg_PSW = 0b00001000; 
    Serial.print(" - Register Bank = "); Serial.println((Reg_PSW & 0b00011000)>>3);
    
    if (flag_opcode_ena){
        Reg_PC = Reg_PC+n_byte;
   }
   Serial.print(" - Reg_PC : ");      Serial.println(Reg_PC,HEX);
}

void Execute_opcode(unsigned short opcode){
unsigned short temp_Reg_bank=0;
unsigned short add_Reg_bank =0;

     temp_Reg_bank=(Reg_PSW & 0b00011000)>>3;
     add_Reg_bank = (temp_Reg_bank*8);
     switch (opcode){
        case 0x00:
                  Serial.print(" - NOP : "); 
                  break;
        case 0x01:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x02: // LJMP code addr
                  Reg_PC = (Reg_cash[0] << 8) | Reg_cash[1];
                  Serial.print(" - LJMP Target PC : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x03:
                  Reg_A = ((Reg_A >> 1) | ((Reg_A & 0x01) << 7)) & 0x00FF;
                  Serial.print(" - RR A : A = "); Serial.println(Reg_A, HEX);
                  break;
        case 0x04:
                  Reg_A = (Reg_A + 1) & 0x00FF; 
                  Serial.print(" - INC A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x05:
                  In_Data_Mem[Reg_cash[0]] = (In_Data_Mem[Reg_cash[0]] + 1) & 0x00FF;
                  Serial.print(" - INC Mem = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x06:
                  In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]] = (In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]] + 1) & 0x00FF;
                  Serial.print(" - INC @R0 : "); 
                  Serial.println(In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]], HEX);
                  break;
        case 0x07:
                  In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]] = (In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]] + 1) & 0x00FF;
                  Serial.print(" - INC @R1 : "); 
                  Serial.println(In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]], HEX);
                  break;
        case 0x08:
                  In_Data_Mem[add_Reg_bank + 0x00] = (In_Data_Mem[add_Reg_bank + 0x00] + 1) & 0x00FF;
                  Serial.print(" - INC R0 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x00], HEX);
                  break;
        case 0x09:
                  In_Data_Mem[add_Reg_bank + 0x01] = (In_Data_Mem[add_Reg_bank + 0x01] + 1) & 0x00FF;  
                  Serial.print(" - INC R1 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x01], HEX);
                  break;
        case 0x0A:
                  In_Data_Mem[add_Reg_bank + 0x02] = (In_Data_Mem[add_Reg_bank + 0x02] + 1) & 0x00FF;  
                  Serial.print(" - INC R2 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x02], HEX);
                  break;
        case 0x0B:
                  In_Data_Mem[add_Reg_bank + 0x03] = (In_Data_Mem[add_Reg_bank + 0x03] + 1) & 0x00FF;  
                  Serial.print(" - INC R3 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x03], HEX);
                  break;
        case 0x0C:
                  In_Data_Mem[add_Reg_bank + 0x04] = (In_Data_Mem[add_Reg_bank + 0x04] + 1) & 0x00FF;  
                  Serial.print(" - INC R4 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x04], HEX);
                  break;
        case 0x0D:
                  In_Data_Mem[add_Reg_bank + 0x05] = (In_Data_Mem[add_Reg_bank + 0x05] + 1) & 0x00FF;  
                  Serial.print(" - INC R5 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x05], HEX);
                  break;
        case 0x0E:
                  In_Data_Mem[add_Reg_bank + 0x06] = (In_Data_Mem[add_Reg_bank + 0x06] + 1) & 0x00FF;  
                  Serial.print(" - INC R6 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x06], HEX);
                  break;
        case 0x0F:
                  In_Data_Mem[add_Reg_bank + 0x07] = (In_Data_Mem[add_Reg_bank + 0x07] + 1) & 0x00FF;  
                  Serial.print(" - INC R7 : "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x07], HEX);
                  break;
        case 0x10: // JBC bit, rel
                  // ตรวจสอบว่าบิตที่ระบุเป็น 1 หรือไม่? 
                  // (ใช้สูตร Byte: 0x20 + Reg_cash[0]>>3 และ BitMask: 1 << (Reg_cash[0]&0x07))
                  if (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] & (1 << (Reg_cash[0] & 0x07))) {   
                      // 1. ถ้าจริง ให้ Clear Bit นั้นเป็น 0 (ใช้ Bitwise AND กับ NOT Mask)
                      In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] &= ~(1 << (Reg_cash[0] & 0x07));
                      // 2. กระโดด (Jump Relative) โดยบวกค่า Offset (ต้อง Cast เป็น signed char เพื่อให้ถอยหลังได้)
                      Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                      Serial.print(" - JBC Taken (Bit Cleared). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                      Serial.println(" - JBC Not Taken.");
                  }
                  break;
        case 0x11:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x12:                   
                  Stack_Mem[Reg_SP] = (Reg_PC>>8) & 0x00FF; // Byte High
                  Reg_SP = Reg_SP +1;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);    // Byte Low
                  Reg_PC = (Reg_cash[0] <<8);
                  Reg_PC = Reg_PC | Reg_cash[1];
                  Serial.print(" - Reg_PC : ");      Serial.println(Reg_PC,HEX);                  
                  break;
        case 0x13:
                  Reg_cash[0] = Reg_PSW & 0x80; 
                  Reg_PSW = (Reg_PSW & 0x7F) | ((Reg_A & 0x01) << 7);
                  Reg_A = (Reg_A >> 1) | Reg_cash[0];
                  Reg_A = Reg_A & 0x00FF;
                  Serial.print(" - RRC A = "); Serial.print(Reg_A, HEX);
                  Serial.print(", CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  break;
        case 0x14: // DEC A
                  Reg_A = (Reg_A - 1) & 0x00FF;
                  Serial.print(" - DEC A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x15:
                  In_Data_Mem[Reg_cash[0]] = (In_Data_Mem[Reg_cash[0]] - 1) & 0x00FF;
                  Serial.print(" - DEC Mem : "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x16:
                  In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]] = (In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]] - 1) & 0x00FF;
                  Serial.print(" - DEC @R0 : "); Serial.println(In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]], HEX);
                  break;
        case 0x17:
                  In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]] = (In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]] - 1) & 0x00FF;
                  Serial.print(" - DEC @R1 : "); Serial.println(In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]], HEX);
                  break;
        case 0x18:
                  In_Data_Mem[add_Reg_bank + 0x00] = (In_Data_Mem[add_Reg_bank + 0x00] - 1) & 0x00FF;
                  Serial.print(" - DEC R0 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x00], HEX);
                  break;
        case 0x19:
                  In_Data_Mem[add_Reg_bank + 0x01] = (In_Data_Mem[add_Reg_bank + 0x01] - 1) & 0x00FF;
                  Serial.print(" - DEC R1 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x01], HEX);
                  break;
        case 0x1A:
                  In_Data_Mem[add_Reg_bank + 0x02] = (In_Data_Mem[add_Reg_bank + 0x02] - 1) & 0x00FF;
                  Serial.print(" - DEC R2 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x02], HEX);
                  break;
        case 0x1B:
                  In_Data_Mem[add_Reg_bank + 0x03] = (In_Data_Mem[add_Reg_bank + 0x03] - 1) & 0x00FF;
                  Serial.print(" - DEC R3 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x03], HEX);
                  break;
        case 0x1C:
                  In_Data_Mem[add_Reg_bank + 0x04] = (In_Data_Mem[add_Reg_bank + 0x04] - 1) & 0x00FF;
                  Serial.print(" - DEC R4 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x04], HEX);
                  break;
        case 0x1D:
                  In_Data_Mem[add_Reg_bank + 0x05] = (In_Data_Mem[add_Reg_bank + 0x05] - 1) & 0x00FF;
                  Serial.print(" - DEC R5 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x05], HEX);
                  break;
        case 0x1E:
                  In_Data_Mem[add_Reg_bank + 0x06] = (In_Data_Mem[add_Reg_bank + 0x06] - 1) & 0x00FF;
                  Serial.print(" - DEC R6 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x06], HEX);
                  break;
        case 0x1F:
                  In_Data_Mem[add_Reg_bank + 0x07] = (In_Data_Mem[add_Reg_bank + 0x07] - 1) & 0x00FF;
                  Serial.print(" - DEC R7 : "); Serial.println(In_Data_Mem[add_Reg_bank + 0x07], HEX);
                  break;
        case 0x20:
                  if ( In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] & (1 << (Reg_cash[0] & 0x07)) ) {
                      Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                      Serial.print(" - JB Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                      Serial.println(" - JB Not Taken.");
                  }
                  break;
        case 0x21:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x22:  
                  Serial.print(" - Reg_SP : ");      Serial.println(Reg_SP,HEX); 
                  Serial.print(" - Stack_Mem : ");      Serial.println(Stack_Mem[Reg_SP],HEX);
                  Serial.print(" - Stack_Mem : ");      Serial.println(Stack_Mem[Reg_SP-1],HEX);
                  
                  if (flag_opcode_ena){    
                     Reg_PC = 0x0000;      
                     Reg_PC = Stack_Mem[Reg_SP];   
                     Reg_SP = Reg_SP-1;
                     Reg_PC = Reg_PC | (Stack_Mem[Reg_SP]<<8); 
                  }
                  // Read opcode til this command                  
                  if (flag_opcode_ena) flag_opcode_ena = false; 
                  
                  Serial.print(" - Reg_PC : ");      Serial.println(Reg_PC,HEX);                  
                  break;
        case 0x23: // RL A (หมุนซ้าย)
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = ((Reg_A << 1) | (Reg_A >> 7)) & 0xFF;
                  Serial.print(" - RL A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x24: // ADD A, #data (ใช้ Reg_cash[0] เป็นตัวบวกตรงๆ)
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  // 1. คำนวณ CY (Carry) : ถ้าผลบวกเกิน 255
                  if ((Reg_A + Reg_cash[0]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  // 2. คำนวณ AC (Aux Carry) : เช็คการทดจากบิต 3 ไป 4
                  if ((Reg_A & 0x0F) + (Reg_cash[0] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  // 3. คำนวณ OV (Overflow) : เช็คเครื่องหมายผิดปกติ 
                  // สูตร: (Old_A ^ Sum) & (Operand ^ Sum) & 0x80
                  if ( ((Reg_A ^ (Reg_A + Reg_cash[0])) & (Reg_cash[0] ^ (Reg_A + Reg_cash[0])) & 0x80) ) 
                      Reg_PSW |= 0x04; 
                  else 
                      Reg_PSW &= ~0x04;
                  // 4. อัปเดตค่า A (ทำเป็นสิ่งสุดท้าย!)
                  Reg_A = (Reg_A + Reg_cash[0]) & 0xFF;
                  Serial.print(" - ADD A,#data : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x25: // ADD A, data_addr
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[Reg_cash[0]]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[Reg_cash[0]] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[Reg_cash[0]])) & (In_Data_Mem[Reg_cash[0]] ^ (Reg_A + In_Data_Mem[Reg_cash[0]])) & 0x80) ) 
                      Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[Reg_cash[0]]) & 0xFF;
                  Serial.print(" - ADD A,data_addr : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x26: // ADD A, @R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  // R0 อยู่ที่ In_Data_Mem[add_Reg_bank]
                  // ข้อมูลที่ R0 ชี้ไป คือ In_Data_Mem[ In_Data_Mem[add_Reg_bank] ]
                  if ((Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank]]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[In_Data_Mem[add_Reg_bank]] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank]])) & (In_Data_Mem[In_Data_Mem[add_Reg_bank]] ^ (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank]])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank]]) & 0xFF;
                  Serial.print(" - ADD A,@R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x27: // ADD A, @R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  // R1 อยู่ที่ In_Data_Mem[add_Reg_bank + 1]
                  if ((Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]])) & (In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]] ^ (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[In_Data_Mem[add_Reg_bank + 1]]) & 0xFF;
                  Serial.print(" - ADD A,@R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x28: // ADD A, R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x00]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x00] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x00])) & (In_Data_Mem[add_Reg_bank + 0x00] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x00])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x00]) & 0xFF;
                  Serial.print(" - ADD A,R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x29:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x01]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x01] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x01])) & (In_Data_Mem[add_Reg_bank + 0x01] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x01])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x01]) & 0xFF;
                  Serial.print(" - ADD A,R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2A:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x02]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x02] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x02])) & (In_Data_Mem[add_Reg_bank + 0x02] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x02])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x02]) & 0xFF;
                  Serial.print(" - ADD A,R2 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2B:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x03]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x03] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x03])) & (In_Data_Mem[add_Reg_bank + 0x03] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x03])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x03]) & 0xFF;
                  Serial.print(" - ADD A,R3 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2C:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x04]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x04] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x04])) & (In_Data_Mem[add_Reg_bank + 0x04] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x04])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x04]) & 0xFF;
                  Serial.print(" - ADD A,R4 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2D:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x05]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x05] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x05])) & (In_Data_Mem[add_Reg_bank + 0x05] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x05])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x05]) & 0xFF;
                  Serial.print(" - ADD A,R5 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2E:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x06]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x06] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x06])) & (In_Data_Mem[add_Reg_bank + 0x06] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x06])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x06]) & 0xFF;
                  Serial.print(" - ADD A,R6 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x2F:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  if ((Reg_A + In_Data_Mem[add_Reg_bank + 0x07]) > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (In_Data_Mem[add_Reg_bank + 0x07] & 0x0F) > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if ( ((Reg_A ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x07])) & (In_Data_Mem[add_Reg_bank + 0x07] ^ (Reg_A + In_Data_Mem[add_Reg_bank + 0x07])) & 0x80) ) 
                        Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = (Reg_A + In_Data_Mem[add_Reg_bank + 0x07]) & 0xFF;
                  Serial.print(" - ADD A,R7 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x30: // JNB bit, rel    
                  if ( ! (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] & (1 << (Reg_cash[0] & 0x07))) ) { 
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - JNB Taken (Bit is 0). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                        Serial.println(" - JNB Not Taken (Bit is 1).");
                  }
                  break;
        case 0x31:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x32:  
                  Serial.print(" - Reg_SP : ");      Serial.println(Reg_SP,HEX); 
                  Serial.print(" - Stack_Mem : ");      Serial.println(Stack_Mem[Reg_SP],HEX);
                  Serial.print(" - Stack_Mem : ");      Serial.println(Stack_Mem[Reg_SP-1],HEX);
                  
                  if (flag_opcode_ena){    
                     Reg_PC = 0x0000;      
                     Reg_PC = Stack_Mem[Reg_SP];   
                     Reg_SP = Reg_SP-1;
                     Reg_PC = Reg_PC | (Stack_Mem[Reg_SP]<<8); 
                  }
                  // Read opcode til this command                  
                  if (flag_opcode_ena) flag_opcode_ena = false; 
                  
                  Serial.print(" - Reg_PC : ");      Serial.println(Reg_PC,HEX);                  
                  break;
        case 0x33: // RLC A (หมุนซ้ายผ่านตัวทด)
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  // เก็บ CY เดิม และ Bit 7 เดิมไว้ก่อน
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short old_bit7 = (Reg_A & 0x80) >> 7;
                  // 1. หมุน A ไปซ้าย 1 ที แล้วเอา CY เดิมไปใส่ที่ Bit 0
                  Reg_A = ((Reg_A << 1) | old_cy) & 0xFF;
                  // 2. เอา Bit 7 เดิม ไปใส่ที่ CY (Bit 7 ของ PSW)
                  if (old_bit7) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  Serial.print(" - RLC A : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x34: // ADDC A, #data
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7; // อ่านตัวทดเก่า (0 หรือ 1)
                  unsigned short operand = Reg_cash[0];
                  // คำนวณผลรวมรวมตัวทด (เพื่อใช้เช็ค Flag)
                  unsigned int sum = Reg_A + operand + old_cy;
                  // Logic Flags (เช็คจาก sum ที่รวมตัวทดแล้ว)
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80; // CY
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40; // AC
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04; // OV

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,#data : "); Serial.println(Reg_A, HEX);
              }
              break;

        case 0x35: // ADDC A, data_addr
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[Reg_cash[0]];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,mem : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x36: // ADDC A, @R0
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]]; // @R0
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,@R0 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x37: // ADDC A, @R1
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]]; // @R1
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,@R1 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x38: // ADDC A, R0
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x00]; // R0
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R0 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x39: // ADDC A, R1
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x01]; // R1
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R1 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3A:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x02];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R2 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3B:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x03];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R3 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3C:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x04];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R4 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3D:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x05];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R5 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3E:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x06];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R6 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x3F:
                  {
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x07];
                  unsigned int sum = Reg_A + operand + old_cy;
                  if (sum > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) + (operand & 0x0F) + old_cy > 0x0F) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  if (((Reg_A ^ sum) & (operand ^ sum) & 0x80)) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Reg_A = sum & 0xFF;
                  Serial.print(" - ADDC A,R7 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x40: // JC 
                  // ตรวจสอบ Carry Flag (Bit 7 ของ PSW) ว่าเป็น 1 หรือไม่?
                  if (Reg_PSW & 0x80) {// ถ้าเงื่อนไขจริง (CY = 1) ให้กระโดด// ต้อง Cast เป็น (signed char) เพื่อให้กระโดดถอยหลังได้             
                      Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                      Serial.print(" - JC Taken (CY=1). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                      Serial.println(" - JC Not Taken (CY=0).");// ถ้าเงื่อนไขเท็จ (CY = 0) ไม่ต้องทำอะไร (PC เดินหน้าไปแล้วใน Fetch/Decode)
                  }
                  break;
        case 0x41:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x42: // ORL data_addr, A (เปลี่ยนค่าใน Memory) // อ่านค่าเดิมจาก Mem -> OR กับ A -> เก็บกลับที่เดิม
                  In_Data_Mem[Reg_cash[0]] |= Reg_A;
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x43: // ORL data_addr, #data (เปลี่ยนค่าใน Memory)// อ่านค่าเดิมจาก Mem -> OR กับค่าคงที่ (Reg_cash[1]) -> เก็บกลับที่เดิม
                  In_Data_Mem[Reg_cash[0]] |= Reg_cash[1];
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x44: // ORL A, #data
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= Reg_cash[0];
                  Serial.print(" - ORL A,#data : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x45: // ORL A, data_addr
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[Reg_cash[0]];
                  Serial.print(" - ORL A,mem : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x46: // ORL A, @R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]];
                  Serial.print(" - ORL A,@R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x47: // ORL A, @R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]];
                  Serial.print(" - ORL A,@R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x48: // ORL A, R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - ORL A,R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x49: // ORL A, R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - ORL A,R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4A:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - ORL A,R2 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4B:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - ORL A,R3 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4C:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - ORL A,R4 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4D:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - ORL A,R5 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4E:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - ORL A,R6 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x4F:
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A |= In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - ORL A,R7 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x50: 
                  if ( !(Reg_PSW & 0x80) ) {
                  Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                  Serial.print(" - JNC Taken (CY=0). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                  Serial.println(" - JNC Not Taken (CY=1).");
                  }
                  break;
        case 0x51:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;         
        case 0x52: // ANL data_addr, A (แก้ไขค่าใน Memory)
                  In_Data_Mem[Reg_cash[0]] &= Reg_A;
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x53: // ANL data_addr, #data (แก้ไขค่าใน Memory)
                  In_Data_Mem[Reg_cash[0]] &= Reg_cash[1];
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x54: // ANL A, #data 
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= Reg_cash[0];
                  Serial.print(" - ANL A,#data : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x55: // ANL A, data_addr
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[Reg_cash[0]];
                  Serial.print(" - ANL A,mem : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x56: // ANL A, @R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]];
                  Serial.print(" - ANL A,@R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x57: // ANL A, @R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]];
                  Serial.print(" - ANL A,@R1 : "); Serial.println(Reg_A, HEX);
                  break;

        case 0x58: // ANL A, R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - ANL A,R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x59: // ANL A, R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - ANL A,R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5A: // ANL A, R2
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - ANL A,R2 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5B: // ANL A, R3
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - ANL A,R3 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5C: // ANL A, R4
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - ANL A,R4 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5D: // ANL A, R5
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - ANL A,R5 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5E: // ANL A, R6
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - ANL A,R6 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x5F: // ANL A, R7
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A &= In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - ANL A,R7 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x60: // JZ 
                  if (Reg_A == 0) {
                  Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                  Serial.print(" - JZ Taken (A=0). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                  Serial.println(" - JZ Not Taken (A!=0).");
                  }
                  break;
        case 0x61:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x62: // XRL data_addr, A (แก้ค่าใน Mem)
                  In_Data_Mem[Reg_cash[0]] ^= Reg_A;
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x63: // XRL data_addr, #data (แก้ค่าใน Mem)
                  In_Data_Mem[Reg_cash[0]] ^= Reg_cash[1];
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;
        case 0x64: // XRL A, #data
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= Reg_cash[0];
                  Serial.print(" - XRL A,#data : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x65: // XRL A, data_addr
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[Reg_cash[0]];
                  Serial.print(" - XRL A,mem : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x66: // XRL A, @R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]];
                  Serial.print(" - XRL A,@R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x67: // XRL A, @R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]];
                  Serial.print(" - XRL A,@R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x68: // XRL A, R0
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - XRL A,R0 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x69: // XRL A, R1
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - XRL A,R1 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6A: // XRL A, R2
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - XRL A,R2 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6B: // XRL A, R3
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - XRL A,R3 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6C: // XRL A, R4
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - XRL A,R4 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6D: // XRL A, R5
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - XRL A,R5 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6E: // XRL A, R6
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - XRL A,R6 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x6F: // XRL A, R7
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A ^= In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - XRL A,R7 : "); Serial.println(Reg_A, HEX);
                  break;
        case 0x70: // JNZ 
                  if (Reg_A != 0) { 
                  Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                  Serial.print(" - JNZ Taken (A!=0). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                  Serial.println(" - JNZ Not Taken (A=0).");
                  }
                  break;
        case 0x71:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x72: // ORL C, bit (เอาค่าบิตที่กำหนด มา OR ใส่ Carry Flag)
                  {
                  unsigned short bit_val = (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] >> (Reg_cash[0] & 0x07)) & 0x01;
                  unsigned short cy_val = (Reg_PSW & 0x80) >> 7;
                  if (cy_val | bit_val) Reg_PSW |= 0x80; // Set CY=1
                  else Reg_PSW &= ~0x80; // Clear CY=0
                  Serial.print(" - ORL C, bit. Result CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
             break;
        case 0x73: // JMP @A+DPTR (กระโดดไปที่ A + DPTR)
                  {
                  // บวกกันตรงๆ (Reg_A เป็น 8-bit, Reg_DPTR เป็น 16-bit)
                  Reg_PC = Reg_DPTR + Reg_A;
                  Serial.print(" - JMP @A+DPTR. Jump to: "); Serial.println(Reg_PC, HEX);
                  }
                  break;
        case 0x74: // MOV A, #data
                  Reg_A = Reg_cash[0];
                  Serial.print(" - MOV A, #data: "); Serial.println(Reg_A, HEX);
                  break;

        case 0x75: // MOV data_addr, #data 
                  In_Data_Mem[Reg_cash[0]] = Reg_cash[1];
                  Serial.print(" - Memory["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] = "); Serial.println(In_Data_Mem[Reg_cash[0]], HEX);
                  break;

        case 0x76: // MOV @R0, #data 
                  {
                  unsigned short addr = In_Data_Mem[add_Reg_bank + 0x00]; // อ่าน Address จาก R0
                  In_Data_Mem[addr] = Reg_cash[0]; // เขียน Data ลงไป
                  Serial.print(" - Memory["); Serial.print(addr, HEX);
                  Serial.print("] (@R0) = "); Serial.println(In_Data_Mem[addr], HEX);
                  }
                  break;

        case 0x77: // MOV @R1, #data
                  {
                  unsigned short addr = In_Data_Mem[add_Reg_bank + 0x01]; // อ่าน Address จาก R1
                  In_Data_Mem[addr] = Reg_cash[0]; // เขียน Data ลงไป
                  Serial.print(" - Memory["); Serial.print(addr, HEX);
                  Serial.print("] (@R1) = "); Serial.println(In_Data_Mem[addr], HEX);
                  }
                  break;
        case 0x78:
                  In_Data_Mem[add_Reg_bank+0x00] = Reg_cash[0];
                  Serial.print(" - Reg_R0 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x00],HEX);
                  Serial.print(" - Add R0 : ");      Serial.println(add_Reg_bank+0x00,HEX);         
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;
        case 0x79:
                  In_Data_Mem[add_Reg_bank+0x01] = Reg_cash[0];
                  Serial.print(" - Reg_R1 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x01],HEX);
                  Serial.print(" - Add R1 : ");      Serial.println(add_Reg_bank+0x01,HEX);         
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;                  
        case 0x7A:
                  In_Data_Mem[add_Reg_bank+0x02] = Reg_cash[0];
                  Serial.print(" - Reg_R2 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x02],HEX);
                  Serial.print(" - Add R2 : ");      Serial.println(add_Reg_bank+0x02,HEX);         
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;
        case 0x7B:
                  In_Data_Mem[add_Reg_bank+0x03] = Reg_cash[0];
                  Serial.print(" - Reg_R3 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x03],HEX);
                  Serial.print(" - Add R3 : ");      Serial.println(add_Reg_bank+0x03,HEX);         
                  // Read opcode til this command                  
                 // if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;
        case 0x7C:
                  In_Data_Mem[add_Reg_bank+0x04] = Reg_cash[0];
                  Serial.print(" - Reg_R4 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x04],HEX);
                  Serial.print(" - Add R4 : ");      Serial.println(add_Reg_bank+0x04,HEX);         
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;
        case 0x7D:
                  In_Data_Mem[add_Reg_bank+0x05] = Reg_cash[0];
                  Serial.print(" - Reg_R5 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x05],HEX);
                  Serial.print(" - Add R5 : ");      Serial.println(add_Reg_bank+0x05,HEX);         
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;        
                  break;                 
        case 0x7E:
                  In_Data_Mem[add_Reg_bank+0x06] = Reg_cash[0];
                  Serial.print(" - Reg_R6 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x06],HEX);
                  Serial.print(" - Add R6 : ");      Serial.println(add_Reg_bank+0x06,HEX);                
                  break;
        case 0x7F:
                  In_Data_Mem[add_Reg_bank+0x07] = Reg_cash[0];
                  Serial.print(" - Reg_R7 : ");      Serial.println(In_Data_Mem[add_Reg_bank+0x07],HEX);
                  Serial.print(" - Add R7 : ");      Serial.println(add_Reg_bank+0x07,HEX);                 
                  break;
        case 0x80: // SJMP rel
                  Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                  Serial.print(" - SJMP to Address: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x81:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x82: // ANL C, bit (เอาค่าบิต AND กับ Carry Flag)
                  {
                  // 1. หาค่าของบิตที่ระบุ (0 หรือ 1)
                  unsigned short bit_val = (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] >> (Reg_cash[0] & 0x07)) & 0x01;
                  // 2. ถ้า CY เป็น 1 และ Bit นั้นเป็น 1 -> ผลลัพธ์จะเป็น 1
                  if ((Reg_PSW & 0x80) && bit_val) {
                        Reg_PSW |= 0x80; // Set CY
                  } else {
                        Reg_PSW &= ~0x80; // Clear CY
                  }
                  Serial.print(" - ANL C, bit. Result CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
                  break;
        case 0x83: // MOVC A, @A+PC (อ่านข้อมูลจาก Program Memory)
                  {
                  unsigned int target_addr = Reg_PC + Reg_A;
                  Reg_A = Program_Mem(target_addr);
                  Serial.print(" - MOVC A read from ROM["); Serial.print(target_addr, HEX);
                  Serial.print("]. New A = "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x84: // DIV AB (หาร A ด้วย B)
                  {
                  unsigned short val_B = In_Data_Mem[0xF0];// Register B อยู่ที่ Address 0xF0
                  Serial.print(" - A = "); Serial.print(Reg_A);
                  Serial.print(", B = "); Serial.println(val_B);
                  if (val_B == 0) {// กรณีหารด้วย 0 : Set Overflow Flag (OV), Clear Carry Flag (CY)
                        Reg_PSW |= 0x04;  // OV = 1
                        Reg_PSW &= ~0x80; // CY = 0
                        Serial.println(" - Error: Division by Zero (OV=1)");
                  } else {
                        unsigned short quotient = Reg_A / val_B;  // ผลหาร (จำนวนเต็ม)
                        unsigned short remainder = Reg_A % val_B; // เศษเหลือ
                        Reg_A = quotient & 0xFF;        // A เก็บผลหาร
                        In_Data_Mem[0xF0] = remainder;  // B เก็บเศษ
                        // เคลียร์ Flag ทั้งคู่
                        Reg_PSW &= ~0x80; // CY = 0
                        Reg_PSW &= ~0x04; // OV = 0
                        Serial.print(" - DIV Result: A (Quotient) = "); Serial.print(Reg_A);
                        Serial.print(", B (Remainder) = "); Serial.println(In_Data_Mem[0xF0]);
                  }
                  }
                  break;
        case 0x85: // MOV data_addr, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short dest_addr = Reg_cash[1];
                  
                  // ย้ายข้อมูล
                  In_Data_Mem[dest_addr] = In_Data_Mem[src_addr];
                  
                  // แสดงผลตาม Format ที่ต้องการ
                  Serial.print(" - MOV src_addr : "); Serial.println(src_addr, HEX);
                  Serial.print(" - dest_addr : "); Serial.println(dest_addr, HEX);
                  Serial.print(" - Value = "); Serial.println(In_Data_Mem[dest_addr], HEX);
                  }
                  break;
        case 0x86: // MOV data_addr, @R0
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00];
                  unsigned short val = In_Data_Mem[ptr];
                  
                  // แสดงค่าก่อนทำ (Source)
                  Serial.print(" - Read @R0 (Addr 0x"); Serial.print(ptr, HEX);
                  Serial.print(") Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x87: // MOV data_addr, @R1
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned short val = In_Data_Mem[ptr];
                  
                  Serial.print(" - Read @R1 (Addr 0x"); Serial.print(ptr, HEX);
                  Serial.print(") Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x88: // MOV data_addr, R0
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - Read R0 Value: "); Serial.println(val, HEX); // ก่อน
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX); // หลัง
                  }
                  break;
        case 0x89: // MOV data_addr, R1
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - Read R1 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8A: // MOV data_addr, R2
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - Read R2 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8B: // MOV data_addr, R3
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - Read R3 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8C: // MOV data_addr, R4
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - Read R4 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8D: // MOV data_addr, R5
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - Read R5 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8E: // MOV data_addr, R6
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - Read R6 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x8F: // MOV data_addr, R7
                  {
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - Read R7 Value: "); Serial.println(val, HEX);
                  
                  In_Data_Mem[Reg_cash[0]] = val;
                  Serial.print(" - MOV Mem["); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0x90:                  
                  Reg_DPTR   = (Reg_cash[0]<<8)|Reg_cash[1];
                  Serial.print(" - Reg_DPTR : ");      Serial.println(Reg_DPTR,HEX);
                  // Read opcode til this command
                  //if (flag_opcode_ena) flag_opcode_ena = false;                    
                  break;
        case 0x91:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0x92: // MOV bit, C (เอาค่า CY ไปใส่ในบิตที่ระบุ)
                  {
                  unsigned short bit_addr = Reg_cash[0];
                  // 1. ดึงค่า Carry Flag (CY)
                  unsigned short cy_val = (Reg_PSW & 0x80) >> 7;
                  // 2. คำนวณตำแหน่ง Byte และ Mask (สูตรเดียวกับ JBC)
                  unsigned short byte_addr = 0x20 + (bit_addr >> 3);
                  unsigned short bit_mask = (1 << (bit_addr & 0x07));
                  // 3. เขียนค่าลงใน Memory
                  if (cy_val) {
                        In_Data_Mem[byte_addr] |= bit_mask;  // Set bit เป็น 1
                  } else {
                        In_Data_Mem[byte_addr] &= ~bit_mask; // Clear bit เป็น 0
                  }
                  Serial.print(" - MOV Bit[0x"); Serial.print(bit_addr, HEX);
                  Serial.print("] with C ("); Serial.print(cy_val);
                  Serial.print("). Result Byte[0x"); Serial.print(byte_addr, HEX);
                  Serial.print("] = "); Serial.println(In_Data_Mem[byte_addr], HEX);
                  }
                  break;
        case 0x93: // MOVC A, @A+DPTR
                  {
                  unsigned int target_addr = Reg_DPTR + Reg_A;
                  unsigned short rom_val = Program_Mem(target_addr);
                  Serial.print(" - Read ROM[0x"); Serial.print(target_addr, HEX);
                  Serial.print("] Value: "); Serial.println(rom_val, HEX);
                  Reg_A = rom_val & 0xFF;
                  Serial.print(" - MOVC Result A = "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x94: // SUBB A, #data
                  {
                  unsigned short operand = Reg_cash[0];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  
                  // คำนวณแบบ Unsigned เพื่อหา CY
                  // ถ้าตัวตั้ง น้อยกว่า (ตัวลบ + ตัวยืม) แสดงว่าต้องยืม -> CY=1
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80; // CY
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40; // AC
                  
                  // คำนวณแบบ Signed เพื่อหา OV (Overflow)
                  // เช็คว่าผลลัพธ์มันทะลุขอบเขต -128 ถึง +127 หรือไม่
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,#data : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x95: // SUBB A, data_addr
                  {
                  unsigned short operand = In_Data_Mem[Reg_cash[0]];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,mem : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x96: // SUBB A, @R0
                  {
                  unsigned short operand = In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x00]];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,@R0 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x97: // SUBB A, @R1
                  {
                  unsigned short operand = In_Data_Mem[In_Data_Mem[add_Reg_bank + 0x01]];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,@R1 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x98: // SUBB A, R0
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x00];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;

                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R0 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x99: // SUBB A, R1
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R1 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9A: // SUBB A, R2
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x02];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R2 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9B: // SUBB A, R3
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x03];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R3 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9C: // SUBB A, R4
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x04];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R4 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9D: // SUBB A, R5
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x05];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R5 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9E: // SUBB A, R6
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x06];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R6 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0x9F: // SUBB A, R7
                  {
                  unsigned short operand = In_Data_Mem[add_Reg_bank + 0x07];
                  unsigned short old_cy = (Reg_PSW & 0x80) >> 7;
                  unsigned int sub_res = Reg_A - operand - old_cy;
                  if (sub_res > 0xFF) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  if ((Reg_A & 0x0F) < ((operand & 0x0F) + old_cy)) Reg_PSW |= 0x40; else Reg_PSW &= ~0x40;
                  int signed_res = (signed char)Reg_A - (signed char)operand - old_cy;
                  if (signed_res < -128 || signed_res > 127) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  Reg_A = sub_res & 0xFF;
                  Serial.print(" - SUBB A,R7 : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xA0: // ORL C, /bit (OR Carry กับค่า "กลับบิต" ของ bit ที่ระบุ)
                  {
                  // 1. อ่านค่าบิต
                  unsigned short bit_val = (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] >> (Reg_cash[0] & 0x07)) & 0x01;
                  
                  // 2. กลับค่าบิต (0->1, 1->0) โดยใช้เครื่องหมาย !
                  bit_val = !bit_val;

                  // 3. อ่าน Carry
                  unsigned short cy_val = (Reg_PSW & 0x80) >> 7;

                  // 4. OR กัน
                  if (cy_val | bit_val) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;

                  Serial.print(" - ORL C, /bit. Result CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
                  break;
        case 0xA1:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xA2: // MOV C, bit (เอาค่าจากบิตที่ระบุ มาใส่ Carry Flag)
                  {
                  // 1. อ่านค่าบิต (0 หรือ 1) จาก Memory
                  unsigned short bit_val = (In_Data_Mem[0x20 + (Reg_cash[0] >> 3)] >> (Reg_cash[0] & 0x07)) & 0x01;
                  
                  // 2. เอาไปใส่ใน PSW Bit 7 (Carry Flag)
                  if (bit_val) Reg_PSW |= 0x80; // Set CY=1
                  else Reg_PSW &= ~0x80;        // Clear CY=0

                  Serial.print(" - Read Bit[0x"); Serial.print(Reg_cash[0], HEX);
                  Serial.print("] val="); Serial.print(bit_val);
                  Serial.print(" -> New CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
                  break;
        case 0xA3: // INC DPTR (เพิ่มค่า DPTR อีก 1)
                  {
                  Serial.print(" - Old DPTR : "); Serial.println(Reg_DPTR, HEX);
                  Reg_DPTR++; // บวกตรงๆ ได้เลย (ตัวแปร unsigned int 16-bit จะวนลูปเองเมื่อเกิน FFFF)
                  Serial.print(" - New DPTR : "); Serial.println(Reg_DPTR, HEX);
                  }
                  break;
        case 0xA4: // MUL AB (คูณ A ด้วย B)
                  {
                  unsigned short val_B = In_Data_Mem[0xF0]; // อ่าน B (Address 0xF0)
                  Serial.print(" - A = "); Serial.print(Reg_A);
                  Serial.print(", B = "); Serial.println(val_B);
                  // คำนวณผลคูณ (สูงสุด 255*255 = 65025)
                  unsigned int product = (unsigned int)Reg_A * val_B;
                  // จัดเก็บผลลัพธ์
                  Reg_A = product & 0xFF;         // A เก็บ 8 บิตล่าง (Low Byte)
                  In_Data_Mem[0xF0] = (product >> 8) & 0xFF; // B เก็บ 8 บิตบน (High Byte)
                  // จัดการ Flags
                  Reg_PSW &= ~0x80; // CY เป็น 0 เสมอสำหรับ MUL
                  // OV เป็น 1 ถ้าผลคูณมากกว่า 255 (คือ B ไม่เป็น 0)
                  if (product > 0xFF) Reg_PSW |= 0x04; else Reg_PSW &= ~0x04;
                  Serial.print(" - MUL Result: A (Low) = "); Serial.print(Reg_A, HEX);
                  Serial.print(", B (High) = "); Serial.println(In_Data_Mem[0xF0], HEX);
                  }
                  break;
        case 0xA5: // Reserved
                  // มาตรฐาน 8051 ไม่มีคำสั่งนี้ (ถือเป็น NOP หรือ Error)
                  Serial.println(" - Executing Reserved Opcode 0xA5 (Do nothing)");
                  break;
        case 0xA6: // MOV @R0, data_addr (เอาค่าจาก Mem ไปใส่ที่ที่ R0 ชี้)
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr]; // อ่านค่าต้นทาง
                  
                  unsigned short dest_ptr = In_Data_Mem[add_Reg_bank + 0x00]; // อ่าน R0 (Pointer)
                  In_Data_Mem[dest_ptr] = val; // เขียนลงปลายทาง
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write to Mem["); Serial.print(dest_ptr, HEX);
                  Serial.print("] (@R0) Result = "); Serial.println(In_Data_Mem[dest_ptr], HEX);
                  }
                  break;
        case 0xA7: // MOV @R1, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  
                  unsigned short dest_ptr = In_Data_Mem[add_Reg_bank + 0x01]; // อ่าน R1 (Pointer)
                  In_Data_Mem[dest_ptr] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write to Mem["); Serial.print(dest_ptr, HEX);
                  Serial.print("] (@R1) Result = "); Serial.println(In_Data_Mem[dest_ptr], HEX);
                  }
                  break;
        case 0xA8: // MOV R0, data_addr (เอาค่าจาก Mem มาใส่ R0)
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  
                  In_Data_Mem[add_Reg_bank + 0x00] = val; // ใส่ R0
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R0 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xA9: // MOV R1, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x01] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R1 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAA: // MOV R2, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x02] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R2 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAB: // MOV R3, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x03] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R3 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAC: // MOV R4, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x04] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R4 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAD: // MOV R5, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x05] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R5 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAE: // MOV R6, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x06] = val;
                  
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R6 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xAF: // MOV R7, data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  In_Data_Mem[add_Reg_bank + 0x07] = val;
                  Serial.print(" - Read Mem["); Serial.print(src_addr, HEX);
                  Serial.print("] Val="); Serial.println(val, HEX);
                  Serial.print(" - Write R7 Result = "); Serial.println(val, HEX);
                  }
                  break;
        case 0xB0: // ANL C, /bit
                  {
                  // 1. อ่านค่าบิตจาก Memory (0 หรือ 1)
                  // (ใช้สูตรเดิมสำหรับ Internal RAM Bit Address 0x00-0x7F)
                  unsigned short byte_addr = 0x20 + (Reg_cash[0] >> 3);
                  unsigned short bit_mask = (1 << (Reg_cash[0] & 0x07));
                  unsigned short bit_val = (In_Data_Mem[byte_addr] & bit_mask) ? 1 : 0;
                  // 2. อ่านค่า Carry Flag (C)
                  unsigned short cy_val = (Reg_PSW & 0x80) >> 7;
                  // 3. คำนวณ C = C AND (NOT bit)
                  // ผลลัพธ์จะเป็น 1 เมื่อ: C=1 และ bit=0 (เพราะกลับค่าแล้วเป็น 1)
                  if (cy_val && (!bit_val)) {
                        Reg_PSW |= 0x80; // Set C = 1
                  } else {
                        Reg_PSW &= ~0x80; // Clear C = 0
                  }
                  Serial.print(" - ANL C with NOT Bit[0x"); Serial.print(Reg_cash[0], HEX);
                  Serial.print("]. BitVal="); Serial.print(bit_val);
                  Serial.print(" -> New CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
                  break;
        case 0xB1:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xB2: // CPL bit (กลับค่าบิตใน Memory: 0<->1)
                  {
                  unsigned short bit_addr = Reg_cash[0];
                  // 1. คำนวณตำแหน่ง Byte และ Mask (สูตรมาตรฐาน)
                  unsigned short byte_addr = 0x20 + (bit_addr >> 3);
                  unsigned short bit_mask = (1 << (bit_addr & 0x07));
                  // 2. กลับค่าบิตโดยใช้ XOR (Bit เดิม ^ 1 = Bit ตรงข้าม)
                  In_Data_Mem[byte_addr] ^= bit_mask;
                  // (อ่านค่าใหม่มาแสดงผล)
                  unsigned short new_val = (In_Data_Mem[byte_addr] & bit_mask) ? 1 : 0;
                  Serial.print(" - CPL Bit[0x"); Serial.print(bit_addr, HEX);
                  Serial.print("]. New Value = "); Serial.println(new_val);
                  }
                  break;
        case 0xB3: // CPL C (กลับค่า Carry Flag)
                  {
                  Reg_PSW ^= 0x80; // Carry Flag อยู่ที่ Bit 7 ของ PSW  // ใช้ XOR กับ 0x80 (1000 0000) เพื่อกลับค่าเฉพาะบิต 7
                  Serial.print(" - CPL C. New CY = "); Serial.println((Reg_PSW & 0x80) >> 7);
                  }
                  break;
        case 0xB4: // CJNE A, #data, rel
                  {
                  unsigned short val1 = Reg_A;
                  unsigned short val2 = Reg_cash[0]; // Immediate Data
                  // 1. เปรียบเทียบเพื่อ Jump
                  if (val1 != val2) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - CJNE Taken (Not Equal). Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                        Serial.println(" - CJNE Not Taken (Equal).");
                  }
                  // 2. ตั้งค่า Carry Flag (สำคัญมาก!)
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xB5: // CJNE A, data_addr, rel
                  {
                  unsigned short val1 = Reg_A;
                  unsigned short val2 = In_Data_Mem[Reg_cash[0]]; // ค่าจาก Direct Address
                  
                  if (val1 != val2) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - CJNE Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else Serial.println(" - CJNE Not Taken.");

                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xB6: // CJNE @R0, #data, rel
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00];
                  unsigned short val1 = In_Data_Mem[ptr]; // ค่าที่ @R0 ชี้
                  unsigned short val2 = Reg_cash[0];      // Immediate Data
                  
                  if (val1 != val2) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - CJNE Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else Serial.println(" - CJNE Not Taken.");

                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xB7: // CJNE @R1, #data, rel
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned short val1 = In_Data_Mem[ptr];
                  unsigned short val2 = Reg_cash[0];
                  
                  if (val1 != val2) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - CJNE Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else Serial.println(" - CJNE Not Taken.");

                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xB8: // CJNE R0, #data, rel
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x00];
                  unsigned short val2 = Reg_cash[0];
                  
                  if (val1 != val2) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - CJNE Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else Serial.println(" - CJNE Not Taken.");

                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xB9: // CJNE R1
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBA: // CJNE R2
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x02];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBB: // CJNE R3
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x03];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBC: // CJNE R4
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x04];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBD: // CJNE R5
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x05];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBE: // CJNE R6
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x06];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xBF: // CJNE R7
                  {
                  unsigned short val1 = In_Data_Mem[add_Reg_bank + 0x07];
                  unsigned short val2 = Reg_cash[0];
                  if (val1 != val2) { Reg_PC = Reg_PC + (signed char)Reg_cash[1]; Serial.println(" - CJNE Taken."); }
                  else Serial.println(" - CJNE Not Taken.");
                  if (val1 < val2) Reg_PSW |= 0x80; else Reg_PSW &= ~0x80;
                  }
                  break;
        case 0xC0: // PUSH data_addr
                  {
                  unsigned short src_addr = Reg_cash[0];
                  unsigned short val = In_Data_Mem[src_addr];
                  Reg_SP++;// 2. ขยับ Stack Pointer ขึ้น 1 ช่อง (Pre-increment)
                  Stack_Mem[Reg_SP] = val;
                  Serial.print(" - PUSH Value: "); Serial.print(val, HEX);
                  Serial.print(" (from Mem[0x"); Serial.print(src_addr, HEX);
                  Serial.print("]) -> Stack[0x"); Serial.print(Reg_SP, HEX);
                  Serial.println("]");
                  }
                  break;
        case 0xC1:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xC2: // CLR bit (เคลียร์บิตให้เป็น 0)
                  {
                  unsigned short bit_addr = Reg_cash[0];
                  // 1. คำนวณตำแหน่ง Byte และ Mask
                  unsigned short byte_addr = 0x20 + (bit_addr >> 3);
                  unsigned short bit_mask = (1 << (bit_addr & 0x07));
                  // 2. สั่งเคลียร์บิต (AND ด้วยค่าตรงข้ามของ Mask)
                  In_Data_Mem[byte_addr] &= ~bit_mask;
                  Serial.print(" - CLR Bit[0x"); Serial.print(bit_addr, HEX);
                  Serial.print("]. Result Byte[0x"); Serial.print(byte_addr, HEX);
                  Serial.print("] = "); Serial.println(In_Data_Mem[byte_addr], HEX);
                  }
                  break;
        case 0xC3: // CLR C (เคลียร์ Carry Flag)
                  {
                  // Clear Bit 7 ของ PSW
                  Reg_PSW &= ~0x80;
                  Serial.println(" - CLR C. New CY = 0");
                  }
                  break;
        case 0xC4: // SWAP A (สลับ 4 บิตบน กับ 4 บิตล่าง)
                  {
                  Serial.print(" - Reg_A before: "); Serial.println(Reg_A, HEX);
                  unsigned short low_nibble = (Reg_A & 0x0F) << 4;  // เอาล่างไปบน
                  unsigned short high_nibble = (Reg_A & 0xF0) >> 4; // เอาบนลงล่าง
                  Reg_A = low_nibble | high_nibble;
                  Serial.print(" - SWAP A result: "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xC5: // XCH A, data_addr
                  {
                  unsigned short addr = Reg_cash[0];
                  unsigned short temp_val = In_Data_Mem[addr]; // อ่านค่าเดิมจาก Mem
                  
                  Serial.print(" - Swap A("); Serial.print(Reg_A, HEX);
                  Serial.print(") with Mem["); Serial.print(addr, HEX);
                  Serial.print("]("); Serial.print(temp_val, HEX); Serial.println(")");

                  In_Data_Mem[addr] = Reg_A; // เอา A ไปใส่ Mem
                  Reg_A = temp_val;          // เอาค่าเดิมของ Mem มาใส่ A
                  }
                  break;
        case 0xC6: // XCH A, @R0
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00]; // อ่าน Address จาก R0
                  unsigned short temp_val = In_Data_Mem[ptr];
                  
                  Serial.print(" - Swap A with Mem[@R0]. Mem["); Serial.print(ptr, HEX);
                  Serial.print("] was "); Serial.println(temp_val, HEX);

                  In_Data_Mem[ptr] = Reg_A;
                  Reg_A = temp_val;
                  }
                  break;
        case 0xC7: // XCH A, @R1
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01]; // อ่าน Address จาก R1
                  unsigned short temp_val = In_Data_Mem[ptr];
                  
                  Serial.print(" - Swap A with Mem[@R1]. Mem["); Serial.print(ptr, HEX);
                  Serial.print("] was "); Serial.println(temp_val, HEX);

                  In_Data_Mem[ptr] = Reg_A;
                  Reg_A = temp_val;
                  }
                  break;
        case 0xC8: // XCH A, R0
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x00];
                  In_Data_Mem[add_Reg_bank + 0x00] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R0. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xC9: // XCH A, R1
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x01];
                  In_Data_Mem[add_Reg_bank + 0x01] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R1. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCA: // XCH A, R2
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x02];
                  In_Data_Mem[add_Reg_bank + 0x02] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R2. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCB: // XCH A, R3
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x03];
                  In_Data_Mem[add_Reg_bank + 0x03] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R3. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCC: // XCH A, R4
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x04];
                  In_Data_Mem[add_Reg_bank + 0x04] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R4. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCD: // XCH A, R5
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x05];
                  In_Data_Mem[add_Reg_bank + 0x05] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R5. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCE: // XCH A, R6
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x06];
                  In_Data_Mem[add_Reg_bank + 0x06] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R6. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xCF: // XCH A, R7
                  {
                  unsigned short temp_val = In_Data_Mem[add_Reg_bank + 0x07];
                  In_Data_Mem[add_Reg_bank + 0x07] = Reg_A;
                  Reg_A = temp_val;
                  Serial.print(" - Swap A with R7. New A="); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xD0: // POP data_addr
                  {
                  unsigned short dest_addr = Reg_cash[0]; // ที่อยู่ปลายทาง
                  // 1. หยิบของจากยอด Stack ปัจจุบัน
                  unsigned short val = Stack_Mem[Reg_SP];
                  // 2. ลดค่า Stack Pointer ลง (Post-decrement)
                  Reg_SP--; 
                  // 3. เอาของไปใส่ใน Memory ปลายทาง
                  In_Data_Mem[dest_addr] = val;
                  Serial.print(" - POP Value: "); Serial.print(val, HEX);
                  Serial.print(" -> Mem[0x"); Serial.print(dest_addr, HEX);
                  Serial.print("]. New SP = "); Serial.println(Reg_SP, HEX);
                  }
                  break;
        case 0xD1:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xD2: // SETB bit (Set บิตให้เป็น 1)
                  {
                  unsigned short bit_addr = Reg_cash[0];
                  unsigned short byte_addr = 0x20 + (bit_addr >> 3);
                  unsigned short bit_mask = (1 << (bit_addr & 0x07));

                  In_Data_Mem[byte_addr] |= bit_mask; // OR ด้วย 1 เพื่อ Set bit

                  Serial.print(" - SETB Bit[0x"); Serial.print(bit_addr, HEX);
                  Serial.print("]. Result Byte[0x"); Serial.print(byte_addr, HEX);
                  Serial.print("] = "); Serial.println(In_Data_Mem[byte_addr], HEX);
                  }
                  break;
        case 0xD3: // SETB C (Set Carry Flag เป็น 1)
                  Reg_PSW |= 0x80;
                  Serial.println(" - SETB C. New CY = 1");
                  break;
        case 0xD4: // DA A (Decimal Adjust for Addition)
                  {
                  Serial.print(" - Before DA A: "); Serial.println(Reg_A, HEX);
                  unsigned short correction = 0;
                  if ( (Reg_A & 0x0F) > 9 || (Reg_PSW & 0x40) ) {
                        correction += 0x06;
                  }
                  if ( (Reg_A & 0xF0) > 0x90 || (Reg_PSW & 0x80) || (Reg_A + correction > 0x9F) ) { // *เงื่อนไขซับซ้อนตาม Spec Intel
                        correction += 0x60;
                        Reg_PSW |= 0x80; // Set CY ถ้ามีการปรับหลักสิบ
                  }
                  Reg_A = (Reg_A + correction) & 0xFF;
                  Serial.print(" - After DA A: "); Serial.println(Reg_A, HEX);
                  }
                  break;

        case 0xD5: // DJNZ data_addr, rel (ลดค่าใน Mem แล้วเช็ค 0)
                  {
                  unsigned short addr = Reg_cash[0];
                  // 1. ลดค่าใน Memory
                  In_Data_Mem[addr] = (In_Data_Mem[addr] - 1) & 0xFF;
                  Serial.print(" - Decrement Mem[0x"); Serial.print(addr, HEX);
                  Serial.print("] to "); Serial.println(In_Data_Mem[addr], HEX);
                  // 2. ถ้ายังไม่เป็น 0 ให้กระโดด
                  if (In_Data_Mem[addr] != 0) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[1];
                        Serial.print(" - DJNZ Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                        Serial.println(" - DJNZ Not Taken (Value is 0).");
                  }
                  }
                  break;
        case 0xD6: // XCHD A, @R0 (สลับเฉพาะ 4 บิตล่าง)
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00];
                  unsigned short mem_val = In_Data_Mem[ptr];
                  Serial.print(" - XCHD A("); Serial.print(Reg_A, HEX);
                  Serial.print(") with Mem("); Serial.print(mem_val, HEX); Serial.println(")");
                  unsigned short new_A = (Reg_A & 0xF0) | (mem_val & 0x0F);
                  unsigned short new_Mem = (mem_val & 0xF0) | (Reg_A & 0x0F);
                  Reg_A = new_A;
                  In_Data_Mem[ptr] = new_Mem;
                  Serial.print(" - Result A="); Serial.print(Reg_A, HEX);
                  Serial.print(", Mem="); Serial.println(In_Data_Mem[ptr], HEX);
                  }
                  break;
        case 0xD7: // XCHD A, @R1 (สลับเฉพาะ 4 บิตล่าง)
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned short mem_val = In_Data_Mem[ptr];
                  unsigned short new_A = (Reg_A & 0xF0) | (mem_val & 0x0F);
                  unsigned short new_Mem = (mem_val & 0xF0) | (Reg_A & 0x0F);
                  Reg_A = new_A;
                  In_Data_Mem[ptr] = new_Mem;
                  Serial.print(" - Result A="); Serial.print(Reg_A, HEX);
                  Serial.print(", Mem="); Serial.println(In_Data_Mem[ptr], HEX);
                  }
                  break;
        case 0xD8: // DJNZ R0, rel
                  {
                  // 1. ลดค่า R0
                  In_Data_Mem[add_Reg_bank + 0x00] = (In_Data_Mem[add_Reg_bank + 0x00] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - Decrement R0 to "); Serial.println(val, HEX);
                  // 2. เช็คเงื่อนไข
                  if (val != 0) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                        Serial.print(" - DJNZ Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else {
                        Serial.println(" - DJNZ Not Taken (R0 is 0).");
                  }
                  }
                  break;
        case 0xD9: // DJNZ R1, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x01] = (In_Data_Mem[add_Reg_bank + 0x01] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - Decrement R1 to "); Serial.println(val, HEX);
                  if (val != 0) {
                        Reg_PC = Reg_PC + (signed char)Reg_cash[0];
                        Serial.print(" - DJNZ Taken. Jump to: "); Serial.println(Reg_PC, HEX);
                  } else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDA: // DJNZ R2, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x02] = (In_Data_Mem[add_Reg_bank + 0x02] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - Decrement R2 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDB: // DJNZ R3, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x03] = (In_Data_Mem[add_Reg_bank + 0x03] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - Decrement R3 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDC: // DJNZ R4, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x04] = (In_Data_Mem[add_Reg_bank + 0x04] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - Decrement R4 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDD: // DJNZ R5, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x05] = (In_Data_Mem[add_Reg_bank + 0x05] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - Decrement R5 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDE: // DJNZ R6, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x06] = (In_Data_Mem[add_Reg_bank + 0x06] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - Decrement R6 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xDF: // DJNZ R7, rel
                  {
                  In_Data_Mem[add_Reg_bank + 0x07] = (In_Data_Mem[add_Reg_bank + 0x07] - 1) & 0xFF;
                  unsigned short val = In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - Decrement R7 to "); Serial.println(val, HEX);
                  if (val != 0) { Reg_PC = Reg_PC + (signed char)Reg_cash[0]; Serial.println(" - DJNZ Taken."); }
                  else Serial.println(" - DJNZ Not Taken.");
                  }
                  break;
        case 0xE0: 
                  Reg_A=Ex_Data_Mem[Reg_DPTR];      
                  Serial.print(" - Reg_A : ");      Serial.println(Reg_A,HEX);
                  // Read opcode til this command                  
                  //if (flag_opcode_ena) flag_opcode_ena = false;                    
                  break;
        case 0xE1:
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0]; 
                  Serial.print(" - AJMP Target : "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xE2: // MOVX A, @R0 (อ่าน External Ram ที่ตำแหน่ง R0 ชี้)
                  {
                  // 1. อ่านค่า Pointer จาก R0 (8-bit)
                  unsigned short addr_low = In_Data_Mem[add_Reg_bank + 0x00];
                  // *หมายเหตุ: ใน 8051 จริง Address 8-bit บนจะมาจาก Port 2 (P2)
                  // แต่ที่นี่เราสมมติให้เป็น 0 ไปก่อน หรือถ้าคุณมีตัวแปร Reg_P2 ก็เอามาใส่ได้ครับ
                  // unsigned int final_addr = (Reg_P2 << 8) | addr_low;
                  unsigned int final_addr = addr_low; 
                  // 2. อ่านจาก External Memory
                  Reg_A = Ex_Data_Mem[final_addr];
                  Serial.print(" - Read ExtMem[0x"); Serial.print(final_addr, HEX);
                  Serial.print("] (@R0) into A. Val = "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xE3: // MOVX A, @R1
                  {
                  unsigned short addr_low = In_Data_Mem[add_Reg_bank + 0x01];
                  unsigned int final_addr = addr_low; // (สมมติ High Byte = 0)
                  Reg_A = Ex_Data_Mem[final_addr];
                  Serial.print(" - Read ExtMem[0x"); Serial.print(final_addr, HEX);
                  Serial.print("] (@R1) into A. Val = "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xE4: // CLR A (เคลียร์ A เป็น 0)
                  Reg_A = 0x00;
                  Serial.println(" - CLR A. Result A = 0x00");
                  Serial.print(" - Rrg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xE5: // MOV A, data_addr
                  {
                  unsigned short addr = Reg_cash[0];
                  Reg_A = In_Data_Mem[addr];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xE6: // MOV A, @R0
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00]; // อ่าน Address ที่ R0 ชี้
                  Reg_A = In_Data_Mem[ptr];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xE7: // MOV A, @R1
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01]; // อ่าน Address ที่ R1 ชี้
                  Reg_A = In_Data_Mem[ptr];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xE8: // MOV A, R0
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x00];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xE9: // MOV A, R1
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x01];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xEA: // MOV A, R2
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x02];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xEB: // MOV A, R3
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x03];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xEC: // MOV A, R4
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x04];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xED: // MOV A, R5
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x05];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xEE: // MOV A, R6
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x06];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xEF: // MOV A, R7
                  Reg_A = In_Data_Mem[add_Reg_bank + 0x07];
                  Serial.print(" - Reg_A : "); Serial.println(Reg_A, HEX);
                  break;
        case 0xF0: // MOVX @DPTR, A (เขียนค่า A ลง External Memory)
                  {
                  // ใช้ DPTR เป็นตัวชี้ตำแหน่ง (Pointer)
                  // เอาค่าใน A ไปใส่ที่นั่น
                  Ex_Data_Mem[Reg_DPTR] = Reg_A;

                  Serial.print(" - Write A("); Serial.print(Reg_A, HEX);
                  Serial.print(") to ExtMem[0x"); Serial.print(Reg_DPTR, HEX);
                  Serial.print("]. Result = "); Serial.println(Ex_Data_Mem[Reg_DPTR], HEX);
                  }
                  break;
        case 0xF1:
                  Stack_Mem[Reg_SP] = (Reg_PC >> 8) & 0x00FF;
                  Reg_SP = (Reg_SP + 1) & 0xFF;
                  Stack_Mem[Reg_SP] = (Reg_PC & 0x00FF);                  
                  Reg_PC = (Reg_PC & 0xF800) | ((opcode & 0xE0) << 3) | Reg_cash[0];
                  Serial.print(" - Reg_PC : "); Serial.println(Reg_PC, HEX);
                  Serial.print(" - ACALL called. Jump to: "); Serial.println(Reg_PC, HEX);
                  break;
        case 0xF2: // MOVX @R0, A (เขียนค่า A ลง ExtMem ที่ตำแหน่ง R0)
                  {
                  // 1. อ่าน Pointer จาก R0
                  unsigned short addr = In_Data_Mem[add_Reg_bank + 0x00];
                  // 2. เขียนข้อมูล
                  Ex_Data_Mem[addr] = Reg_A;
                  Serial.print(" - Write A("); Serial.print(Reg_A, HEX);
                  Serial.print(") to ExtMem[0x"); Serial.print(addr, HEX);
                  Serial.print("] (@R0). Result = "); Serial.println(Ex_Data_Mem[addr], HEX);
                  }
                  break;
        case 0xF3: // MOVX @R1, A (เขียนค่า A ลง ExtMem ที่ตำแหน่ง R1)
                  {
                  unsigned short addr = In_Data_Mem[add_Reg_bank + 0x01];
                  Ex_Data_Mem[addr] = Reg_A;
                  Serial.print(" - Write A("); Serial.print(Reg_A, HEX);
                  Serial.print(") to ExtMem[0x"); Serial.print(addr, HEX);
                  Serial.print("] (@R1). Result = "); Serial.println(Ex_Data_Mem[addr], HEX);
                  }
                  break;
        case 0xF4: // CPL A (กลับบิต A: 00001111 -> 11110000)
                  {
                  Serial.print(" - Reg_A before: "); Serial.println(Reg_A, HEX);
                  // ใช้เครื่องหมาย ~ (Bitwise NOT)
                  Reg_A = (~Reg_A) & 0xFF; 
                  Serial.print(" - CPL A result: "); Serial.println(Reg_A, HEX);
                  }
                  break;
        case 0xF5: // MOV data_addr, A
                  {
                  unsigned short addr = Reg_cash[0];
                  In_Data_Mem[addr] = Reg_A;
                  
                  Serial.print(" - Write A to Mem[0x"); Serial.print(addr, HEX);
                  // อ่านค่าจาก Memory ปลายทางมาแสดง (ไม่ใช่ Reg_A)
                  Serial.print("]. Value = "); Serial.println(In_Data_Mem[addr], HEX); 
                  }
                  break;
        case 0xF6: // MOV @R0, A
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x00]; // อ่าน Pointer R0
                  In_Data_Mem[ptr] = Reg_A;
                  
                  Serial.print(" - Write A to @R0 [Mem 0x"); Serial.print(ptr, HEX);
                  // อ่านค่าจาก Memory ปลายทางมาแสดง
                  Serial.print("]. Value = "); Serial.println(In_Data_Mem[ptr], HEX); 
                  }
                  break;
        case 0xF7: // MOV @R1, A
                  {
                  unsigned short ptr = In_Data_Mem[add_Reg_bank + 0x01]; // อ่าน Pointer R1
                  In_Data_Mem[ptr] = Reg_A;
                  
                  Serial.print(" - Write A to @R1 [Mem 0x"); Serial.print(ptr, HEX);
                  // อ่านค่าจาก Memory ปลายทางมาแสดง
                  Serial.print("]. Value = "); Serial.println(In_Data_Mem[ptr], HEX);
                  }
                  break;
        case 0xF8: // MOV R0, A
                  In_Data_Mem[add_Reg_bank + 0x00] = Reg_A;
                  Serial.print(" - MOV R0, A. Result R0 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x00], HEX); 
                  break;
        case 0xF9: // MOV R1, A
                  In_Data_Mem[add_Reg_bank + 0x01] = Reg_A;
                  Serial.print(" - MOV R1, A. Result R1 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x01], HEX); 
                  break;
        case 0xFA: // MOV R2, A
                  In_Data_Mem[add_Reg_bank + 0x02] = Reg_A;
                  Serial.print(" - MOV R2, A. Result R2 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x02], HEX); 
                  break;
        case 0xFB: // MOV R3, A
                  In_Data_Mem[add_Reg_bank + 0x03] = Reg_A;
                  Serial.print(" - MOV R3, A. Result R3 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x03], HEX); 
                  break;
        case 0xFC: // MOV R4, A
                  In_Data_Mem[add_Reg_bank + 0x04] = Reg_A;
                  Serial.print(" - MOV R4, A. Result R4 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x04], HEX); 
                  break;
        case 0xFD: // MOV R5, A
                  In_Data_Mem[add_Reg_bank + 0x05] = Reg_A;
                  Serial.print(" - MOV R5, A. Result R5 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x05], HEX);
                  break;
        case 0xFE: // MOV R6, A
                  In_Data_Mem[add_Reg_bank + 0x06] = Reg_A;
                  Serial.print(" - MOV R6, A. Result R6 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x06], HEX); 
                  break;
        case 0xFF: // MOV R7, A
                  In_Data_Mem[add_Reg_bank + 0x07] = Reg_A;
                  Serial.print(" - MOV R7, A. Result R7 = "); 
                  Serial.println(In_Data_Mem[add_Reg_bank + 0x07], HEX);
                  break;
        default:
                  break;
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Test");        Serial.println();
  switch (current_state){
    case 0 :// Fetch state
            if (flag_opcode_ena) Reg_opcode = Program_Mem(Reg_PC);   // Read opcode from program memory            
            
            Serial.println("Fetch State");
            Serial.print(" - Reg_opcode : ");  Serial.println(Reg_opcode,HEX);            
            next_state = 1;
            break;
    case 1 :// Decode state
            Serial.println("Decode State");   
            Decode_opcode(Reg_opcode);         
            next_state = 2;
            break;      
    case 2 :// Execute state

            Serial.println("Execute State");
            Execute_opcode(Reg_opcode);
            next_state = 0;
            break; 
    default:
            next_state = 0;
            break;    
  }
  current_state = next_state;
  delay(4000);
}

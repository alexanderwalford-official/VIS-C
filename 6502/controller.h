/*
    Alexander Walford 2024 - VIS-C
    Open-Source Project: A visual approach to processor emulation.
*/

#ifndef CONTROLLER_H 
#define CONTROLLER_H

// memory addresses array
char memory_addresses[65536][7]; // "0xFFFF" + null terminator, hence 7 not 6

// create an array for the instructions in memory, same size as max memory
uint8_t memory_manager[65536];

// create a custom data structure for the processor (add more registers)
struct {
    uint8_t A;      // accumulator
    uint8_t X;      // X index register
    uint8_t Y;      // Y index register
    uint8_t SP;     // stack pointer
    uint16_t PC;    // program count
    uint8_t P;      // status (flags)
} processor_data;

// a bit un-needed but keeps things easy
void processor_6502_read (uint16_t addr) {
    return memory_manager[addr];
}

// fetches instruction from memory
void processor_6502_fetch_instruction (processor_data *cpu_dt) {
    // read memory and increment program counter
    return processor_6502_read(cpu_dt->PC++);
}

// same story here
void processor_6502_write (uint16_t addr, uint8_t val) {
    memory_manager[addr] = val;
}

// this function resets the processor to its original state
void processor_6502_reset (processor_data *cpu_dt) {
    // load the starting address
    uint8_t low_byte  = memory_manager[0xFFFC];
    uint8_t high_byte = memory[0xFFFD];  

    // combine both bytes into a 16 bit address
    cpu_dt->PC = (high_byte << 8) | low_byte;

    // now we need to reset the registers to 0 (can add more)
    cpu_dt->A = 0;
    cpu_dt->X = 0;
    cpu_dt->Y = 0;

    // set stack pntr to start
    cpu_dt->SP = 0XFD;

    // set init status flags
    cpu_dt->P = 0X24;
}

// execute the operation
void processor_6502_ps (processor_data *cpu_dt) {
    // fetch the operation from memory
    uint8_t op = processor_6502_fetch_instruction(cpu_dt);

    // super fast op code check (apparently switch case is faster???)
    (op == 0x49) ? (cpu_dt->A = processor_6502_fetch_instruction(cpu_dt)) : // set the A register to the value of the instruction
    (op == 0xEA) ? (void)0 :  // NOP
    printf("[ X ] Unknown operation: 0x%02X\n", op);
}

// load a program by iterating all the way through it
void processor_6502_load (uint8_t *program, uint16_t size, uint16_t start_address) {
    // takes the program instructions, the size and the starting address
    for (int i = 0; i < size; i++) { // iterate through the program's full size
        processor_6502_write(start_address + i, program[i]); // write to memory the program value
    }
}

// currently only runs once, could be changed to use a loop if needed
void processor_6502_clock (processor_data *cpu_dt) {
    processor_6502_ps(cpu_dt);
}

// this function is used to display a table-like visualisation of the processor's current operations
void processor_6502_display_graph (processor_data *cpu_dt) {
    printf("TO BE IMPLEMENTED!\n");
}

// will likely be moved to its own header file when we've done a bit more then just assign memory addresses..
void processor_6502 () {
    printf("[ ! ] Assigning memory for ATMEL 6502..\n");

    // assign all memory addresses
    // increment from lowest memory address value to maximum
    for (int i = 0; i < 65536; i++) {
        snprintf(memory_addresses[i], 7, "0x%04X", i);
        //printf("%s\n", memory_addresses[i]);
    }

    // load a sample program
    uint8_t program[] = { 0xA9, 0x42, 0xEA };  // LDA #$42, NOP
    processor_6502_load(program, sizeof(program), 0x8000); // program, size, start address

    // create a processor object
    struct processor_data *cpu_dt;

    // show processor state before execution
    processor_6502_display_graph(cpu_dt);

    // start the clock, for one clock cycle (currently)
    processor_6502_clock(cpu_dt);

    // show processor state after execution
    processor_6502_display_graph(cpu_dt);

    printf("[ ! ] Done assigning memory for all addresses.\n");
    getchar();
}

#endif
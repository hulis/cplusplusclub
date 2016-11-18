#include <memory>
// http://tinyurl.com/hhvmgtn

#include <iostream>

#define MEM_1KB     1024
#define MEM_8KB     MEM_1KB * 8
#define MEM_16KB    MEM_1KB * 16

struct VM {
	char program[MEM_8KB];
	char ram[MEM_16KB];

	// Program counter.
	int pc = 0;
	// Stack pointer.
	int sp = 0;
	// eq-flag.
	int eq = 0;
};

//  - pop
//  - push, arg
//  - add
//  - or
//  - and
//  - eq
//  - jez
//  - jenz
//  - jmp
//  - print(sys call)

#define EXIT        0
#define PUSH        1
#define POP         2
#define ADD         3
#define EQ          4
#define INC         5
#define JMPEQ       6
#define JMP         7
#define PRINT       8

int vm_run(char* program, size_t programLen) {
	VM vm;

	memcpy(vm.program, program, programLen);

	while (true) {
		char op = vm.program[vm.pc];

		if (op == EXIT) {
			break;
		}
		else if (op == PUSH) {
			vm.pc++;

			memcpy(&vm.ram[vm.sp], &vm.program[vm.pc], 4);

			vm.pc += 4;
			vm.sp += 4;
		}
		else if (op == POP) {
			vm.sp -= 4;
			vm.pc++;
		}
		else if (op == ADD) {
			int* a = (int*)&vm.ram[vm.sp - 8];
			int* b = (int*)&vm.ram[vm.sp - 4];

			*a += *b;

			vm.sp -= 8;
			vm.pc++;
		}
		else if (op == EQ) {
			int* a = (int*)&vm.ram[vm.sp - 8];
			int* b = (int*)&vm.ram[vm.sp - 4];

			vm.eq = *a == *b;

			vm.pc++;
		}
		else if (op == INC) {
			int* a = (int*)&vm.ram[vm.sp - 4];

			(*a)++;

			vm.pc++;
		}
		else if (op == JMPEQ) {
			vm.pc++;

			if (vm.eq != 1) {
				vm.pc += 4;

				continue;
			}

			int* address = (int*)&vm.program[vm.pc];

			vm.pc = *address;
		}
		else if (op == JMP) {
			vm.pc++;

			int* address = (int*)&vm.program[vm.pc];

			vm.pc = *address;
		}
		else if (op == PRINT) {
			int* a = (int*)&vm.ram[vm.sp - 4];

			std::cout << *a << std::endl;

			vm.pc++;
		}
		else {
			// Invalid/unsupported op.
			break;
		}
	}

	int retval = *(int*)&vm.ram[vm.sp];

	return retval;
}

int main() {
	char program[] = {
		PUSH, 128, 0, 0, 0,
		PUSH, 64, 0, 0, 0,
		ADD,
		EXIT
	};

	char loop[] = {
		PUSH, 0, 0, 0, 0,
		INC,
		PUSH, 16, 0, 0, 0,
		EQ,
		POP,
		PRINT,
		JMPEQ, 24, 0, 0, 0,
		JMP, 5, 0, 0, 0,
		EXIT
	};

	/*
	push 0
	BEG:
	inc
	push 16
	eq
	pop
	print
	jmpeq EXIT
	jmp BEG
	EXIT:
	exit
	*/

	int retval = vm_run(loop, sizeof(loop));

	std::cout << "ret val of program: " << retval << std::endl;

	system("pause");

	return 0;
}
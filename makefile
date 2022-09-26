default: vm lc3
vm: vm.c
	gcc -Wall vm.c -o vm
	./vm
lc3: lc3.c
	gcc -Wall lc3.c -o lc3-vm
	./lc3-vm
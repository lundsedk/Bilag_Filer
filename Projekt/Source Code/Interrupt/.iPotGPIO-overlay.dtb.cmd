cmd_/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb := mkdir -p /home/stud/Projekt/custom_interupt/driver/ ; gcc -E -Wp,-MD,/home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.dts.tmp /home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dts ; ./scripts/dtc/dtc -O dtb -o /home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb -b 0 -i/home/stud/Projekt/custom_interupt/driver/ -i./scripts/dtc/include-prefixes -Wno-unit_address_vs_reg -Wno-unit_address_format -Wno-gpios_property -Wno-avoid_unnecessary_addr_size -Wno-alias_paths -Wno-graph_child_address -Wno-simple_bus_reg -Wno-unique_unit_address -Wno-pci_device_reg  -d /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.d.dtc.tmp /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.dts.tmp ; cat /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.d.pre.tmp /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.d.dtc.tmp > /home/stud/Projekt/custom_interupt/driver/.iPotGPIO-overlay.dtb.d

source_/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb := /home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dts

deps_/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb := \

/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb: $(deps_/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb)

$(deps_/home/stud/Projekt/custom_interupt/driver/iPotGPIO-overlay.dtb):

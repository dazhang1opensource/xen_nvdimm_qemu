#ifndef QEMU_HW_XEN_H
#define QEMU_HW_XEN_H

/*
 * public xen header
 *   stuff needed outside xen-*.c, i.e. interfaces to qemu.
 *   must not depend on any xen headers being present in
 *   /usr/include/xen, so it can be included unconditionally.
 */

#include "qemu-common.h"
#include "exec/cpu-common.h"
#include "hw/acpi/aml-build.h"
#include "hw/irq.h"

/* xen-machine.c */
enum xen_mode {
    XEN_EMULATE = 0,  // xen emulation, using xenner (default)
    XEN_CREATE,       // create xen domain
    XEN_ATTACH        // attach to xen domain created by xend
};

extern uint32_t xen_domid;
extern enum xen_mode xen_mode;
extern bool xen_domid_restrict;

extern bool xen_allowed;

static inline bool xen_enabled(void)
{
    return xen_allowed;
}

int xen_pci_slot_get_pirq(PCIDevice *pci_dev, int irq_num);
void xen_piix3_set_irq(void *opaque, int irq_num, int level);
void xen_piix_pci_write_config_client(uint32_t address, uint32_t val, int len);
void xen_hvm_inject_msi(uint64_t addr, uint32_t data);
int xen_is_pirq_msi(uint32_t msi_data);

qemu_irq *xen_interrupt_controller_init(void);

void xenstore_store_pv_console_info(int i, struct Chardev *chr);

void xen_hvm_init(PCMachineState *pcms, MemoryRegion **ram_memory);

void xen_ram_alloc(ram_addr_t ram_addr, ram_addr_t size,
                   struct MemoryRegion *mr, Error **errp);
void xen_hvm_modified_memory(ram_addr_t start, ram_addr_t length);

void xen_register_framebuffer(struct MemoryRegion *mr);

void xen_acpi_build(AcpiBuildTables *tables, GArray *table_offsets,
                    MachineState *machine);

size_t xen_copy_to_guest(ram_addr_t gpa, void *buf, size_t length);
size_t xen_copy_from_guest(ram_addr_t gpa, void *buf, size_t length);

int xen_rw_host_pmem(ram_addr_t hpa, void *buf, size_t length, bool is_write);
#define xen_read_host_pmem(hpa, buf, len) \
    xen_rw_host_pmem((hpa), (buf), (len), false)
#define xen_write_host_pmem(hpa, buf, len) \
    xen_rw_host_pmem((hpa), (void *)(buf), (len), true)

#endif /* QEMU_HW_XEN_H */

---
name: qemu-change
description: "修改 QEMU 设备模型、QAPI、KVM 加速、迁移或机器类型时使用。用户提到 QEMU、QOM、QMP、hw/、accel/kvm 或机器属性时也要使用。"
---

# 改这棵 QEMU

先读仓库根目录的 `CODING_STYLE` 和 `HACKING`。这是 meson 之前的树：`qemu` 是 3.0.50，`xen_nvdimm_qemu` 是 2.11.50。缩进 4 个空格，不用 tab。花括号跟同文件保持一致。

- 设备放在 `hw/<子系统>/`，类型用 QOM，属性用已有的 `DEFINE_PROP_*`。
- 客人能看见的行为（寄存器、ACPI、PCI ID、迁移段）有变化时，提交说明里写兼容性。能加机器类型属性，就不要改旧机器的默认行为。
- QMP 从 `qapi/` 加。2.11 还有根目录的 `qapi-schema.json`。生成文件不要手改。
- KVM 改动同时看 `linux-headers/` 和对应内核的 uapi。两边不一致就停下来说明。
- 内存用 `MemoryRegion`。不要绕过已有 region 直接写客户机物理内存。
- 构建是 `configure` 加 `Makefile.objs`。新文件加进对应的 `Makefile.objs`，不要引入 meson。
- 提交标题用 `子系统: 一句话`。正文格式跟 `git log` 里同目录最近的提交走。

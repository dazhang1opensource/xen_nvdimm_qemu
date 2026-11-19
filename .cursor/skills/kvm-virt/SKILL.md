---
name: kvm-virt
description: "修改 KVM、虚拟化加速或 QEMU 的 KVM 后端时使用。用户提到 KVM ioctl、kvm_vcpu、accel/kvm、虚拟机退出、内存槽、中断注入或 VFIO 直通时也要使用。"
---

# KVM 与虚拟化边界

内核侧和 QEMU 侧分开看。用户态 ABI 以两边同时存在的定义为准。

## 内核树

这棵 Linux 是 5.0-rc1。公共代码在 `virt/kvm/`，架构代码在 `arch/<arch>/kvm/`。x86 的 ioctl 在 `include/uapi/linux/kvm.h` 和 `arch/x86/include/uapi/asm/kvm.h`。

- `KVM_GET_*`、`KVM_SET_*` 和 `kvm_run` 是用户态 ABI。加字段只能追加，旧的用户态还要能跑。
- 新能力用 `KVM_CAP_*`，接到这棵树里已有的 extension 检查函数上。不要改已有 cap 的含义。
- vcpu 运行、中断注入、MMU 和 I/O 退出是不同路径。改一条时写明另外几条看到的状态。
- 设备直通走 VFIO 和 irqfd、ioeventfd。不要在 KVM 里直接碰驱动的私有结构。

## QEMU 树

3.0 的 KVM 在 `accel/kvm/` 和 `target/<arch>/kvm.c`。头文件同步区是 `linux-headers/`。它和内核 uapi 不一致时，先指出差在哪，不要只改一边。

- 要随迁移走的状态放进已有的 VMState。不要把指针塞进迁移流。
- 新的客户机可见属性走这棵树已有的 QAPI 和 QOM。生成文件不要手改。

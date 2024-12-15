---
generator: doxide
---


# Kernel

**class Kernel**

The kernel class is the core of Capi's OS. It manages hardware and interrupts, as
well as setting up the system at boot time.


## Types

| Name | Description |
| ---- | ----------- |
| [ShutdownMode](Kernel/ShutdownMode.md) | An enumeration specifying the possible shutdown modes in Capi. |
| [Multicore](Kernel/Multicore.md) | A class implementing support for using all the cores of the Pi's CPU. |

## Functions

| Name | Description |
| ---- | ----------- |
| [Kernel](#Kernel) | Create the kernel instance. |
| [initialize](#initialize) | Initializes the kernel. |
| [updateUSB](#updateUSB) | Updates the USB driver. |
| [run](#run) | Enters the kernel's main loop. |
| [magicRebootStringHandler](#magicRebootStringHandler) | The method which handles the debug cable sending the "magic" string that causes a system reboot.;  |
| [mouseRemovedHandler](#mouseRemovedHandler) | The method which handles the mouse being unplugged. |
| [keyboardRemovedHandler](#keyboardRemovedHandler) | The method which handles the keyboard being unplugged. |

## Function Details

### Kernel<a name="Kernel"></a>
!!! function "Kernel()"

    Create the kernel instance. There should only ever be one active instance of this
    class.
    

### initialize<a name="initialize"></a>
!!! function "method initialize() -&gt; Bool"

    Initializes the kernel.
    
    
    :material-keyboard-return: **Return**
    :    true for success, false for falure.
    

### updateUSB<a name="updateUSB"></a>
!!! function "method updateUSB() -&gt; Void"

    Updates the USB driver.
    

### run<a name="run"></a>
!!! function "method run() -&gt; ShutdownMode"

    Enters the kernel's main loop. This must be called after [Kernel::initialize()](#initialize).
    
    
    :material-keyboard-return: **Return**
    :    The shutdown mode for the system.
    

### magicRebootStringHandler<a name="magicRebootStringHandler"></a>
!!! function "static method magicRebootStringHandler() -&gt; Void"

    The method which handles the debug cable sending the "magic" string that causes a system
    reboot.;
    

### mouseRemovedHandler<a name="mouseRemovedHandler"></a>
!!! function "static method mouseRemovedHandler(CDevice &#42;pDevice, void &#42;pContext) -&gt; Void"

    The method which handles the mouse being unplugged.
    
    
    :material-location-enter: `pDevice`
    :    A handle to the Circle CDevice intance for the mouse.
        
    :material-location-enter: `pContext`
    :    A pointer to a context structure holding internal data.
    

### keyboardRemovedHandler<a name="keyboardRemovedHandler"></a>
!!! function "static method keyboardRemovedHandler(CDevice &#42;pDevice, void &#42;pContext) -&gt; Void"

    The method which handles the keyboard being unplugged.
    


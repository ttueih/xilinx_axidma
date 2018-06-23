/**-------------------------------------------------------------------------------------------------------------------
 *
 * Xilinx DMA Bridge Driver Main
 *
 * Author:          Brandon Perez <bmperez@alumni.cmu.edu>
 * Creation Date:   Saturday, November 14, 2015 at 11:20:00 AM EST
 *
 * Description:
 *
 *  This file contains the Xilinx DMA bridge driver's entrypoints for insertion and probing.
 *
 *  This code has the entrypoints for when the driver is initially inserted into the kernel and when it is later probed
 *  when a matching device tree entry is found. These functions mainly call other initialization and cleanup functions
 *  for the various subsystems within the driver (e.g character device, DMA, etc). Also, this is where command-line
 *  arguments, top-level metadata about the driver, and the device tree comp ability string are specified.
 *
 *-------------------------------------------------------------------------------------------------------------------**/

// Kernel Includes
#include <linux/module.h>           // Various module macros, such as init and exit.
#include <linux/moduleparam.h>      // Module parameter macro.
#include <linux/mod_devicetable.h>  // OF device ID structure.
#include <linux/platform_device.h>  // Platform device structure and functions.
#include <linux/slab.h>             // Memory allocation functions and definitions
#include <linux/stat.h>             // Permission constants, for module parameters

/*--------------------------------------------------------------------------------------------------------------------
 * Module Parameters
 *--------------------------------------------------------------------------------------------------------------------*/

/**
 * The name to use for the character device.
 *
 * This defaults to the module's name (xilinx-dma-bridge). This will appear on the Linux filesystem under
 * "/dev/xilinx-dma-bridge", and it acts as the interface to the userspace library.
 **/
#define XILINX_DMA_BRIDGE_DRIVER_NAME       "xilinx-dma-bridge"
static char *CHARACTER_DEVICE_NAME          = XILINX_DMA_BRIDGE_DRIVER_NAME;
module_param(CHARACTER_DEVICE_NAME, charp, S_IRUGO);

/**
 * The minor number to use for the character device associated with the driver, which is 0 by default.
 **/
static int MINOR_NUMBER                     = 0;
module_param(MINOR_NUMBER, int, S_IRUGO);

/*--------------------------------------------------------------------------------------------------------------------
 * Platform Device Functions
 *--------------------------------------------------------------------------------------------------------------------*/

/**
 * Allocates all of the driver's resources and initializes its subsystems when a matching device tree entry is found.
 *
 * This function is invoked when a device tree entry with a matching compatible string is found in the device tree (i.e
 * the driver is probed. This functions simply invokes all of the initialization functions for the driver's subsystems,
 * and sets up some data structure fields.
 **/
static int xilinx_dma_bridge_probe(struct platform_device *pdev)
{
    /* TODO:
     *  1. Get a pointer to the driver private device (global variable)
     *  2. Set the platform device field.
     *  3. Set the character device name
     *  4. Set the number of devices (?)
     *  5. Call the init function for the character device
     *  6. Call the init function for the DMA subsystem.
     **/

    return 0;
}

/**
 * Cleans up all of the driver's resources when the platform driver is removed.
 *
 * This function is invoked when the platform driver unregistered with the kernel. This function simply invokes all of
 * the cleanup functions for the various subsystems in the driver.
 **/
static int xilinx_dma_bridge_remove(struct platform_device *platform_device)
{
    /* TODO:
     *  1. Get the private device from platform device.
     *  2. Cleanup the character device.
     *  3. Cleanup the DMA subsystem.
     **/

    return 0;
}

/**
 * The list of Open Firmware (OF) compatible ID strings that the driver can match against. If a device tree (OF) node's
 * compatible string matches one of these IDs, then it will trigger a probe of the driver.
 **/
static const struct of_device_id device_tree_compatible_ids[] = {
        { .compatible = "xlnx,xilinx-dma-bridge" },
        {},
};

/**
 * The structure representing the platform driver for driver. This mainly has the function table that defines the probe
 * and remove methods for the driver's platform device.
 **/
static struct platform_driver xilinx_dma_bridge_platform_driver = {
        .driver = {
            .name = XILINX_DMA_BRIDGE_DRIVER_NAME,
            .owner = THIS_MODULE,
            .of_match_table = device_tree_compatible_ids,
        },
        .probe = xilinx_dma_bridge_probe,
        .remove = xilinx_dma_bridge_remove,
};

/*--------------------------------------------------------------------------------------------------------------------
 * Module Initialization and Exit
 *--------------------------------------------------------------------------------------------------------------------*/

/**
 * Initializes the Xilinx DMA Bridge driver.
 *
 * This is the entrypoint for when the driver is inserted into the kernel (or when the kernel is booted if the driver
 * is a built-in module). This simply registers the platform device for the driver, which is later triggered if a
 * matching device tree entry for the driver is found.
 **/
static int __init xilinx_dma_bridge_init(void)
{
    return platform_driver_register(&xilinx_dma_bridge_platform_driver);
}

/**
 * Exits or destroys the Xilinx DMA Bridge driver.
 *
 * This function is invoked when the driver is removed from the kernel (or when the kernel is shutdown if the driver is
 * a built-in module). This simply registers the platform device for the driver.
 **/
static void __exit xilinx_dma_bridge_exit(void)
{
    return platform_driver_unregister(&xilinx_dma_bridge_platform_driver);
}

// Register the initialization and exit functions for the driver with the kernel.
module_init(xilinx_dma_bridge_init);
module_exit(xilinx_dma_bridge_exit);

/*-------------------------------------------------------------------------------------------------------------------
 * Module Metadata
 *--------------------------------------------------------------------------------------------------------------------*/

// Define the authors of the driver.
MODULE_AUTHOR("Brandon Perez <bmperez@alumni.cmu.edu>");
MODULE_AUTHOR("Jared Choi");

// Define the driver's license and its version number.
// TODO: Change to MIT license
MODULE_LICENSE("GPL");
MODULE_VERSION("2.0");

// Provide a description for the driver and its purpose.
MODULE_DESCRIPTION("Provides a userspace interface for the various Xilinx DMA hardware IPs (AXI DMA, VDMA, and CDMA),"
        " acting as a bridge between the Xilinx DMA driver and userspace. This is used to transfer data from a"
        " userspace program running on the processor to the FPGA logic fabric via one of Xilinx's DMA IPs.");

# Firmware Management HAL Documentation

## Acronyms

- `HAL` \- Hardware Abstraction Layer
- `RDK-B` \- Reference Design Kit for Broadband Devices
- `OEM` \- Original Equipment Manufacture

## Description

The diagram below describes a high-level software architecture of the  Firmware Management HAL module stack.

![Firmware Management HAL Architecture Diag](images/Firmware_Management_hal_architecture.png)

Firmware Management HAL is an abstraction layer implemented to interact with the vendor software's for getting the hardware specific details of the firmware for the CPE devices.In addition to that downloading status also can be known through the APIs.

## Component Runtime Execution Requirements

### Initialization and Startup

The below mentioned APIs will be used to set the download url,download the firmware from server, commit the firmware on the bank and set the reboot status from the Firmware Management HAL layers/code. 

The client is expected to call the corresponding API in the following order inorder to work properly.

1. fwupgrade_hal_set_download_url
2. fwupgrade_hal_set_download_interface
3. fwupgrade_hal_download
4. fwupgrade_hal_reboot_ready
5. fwupgrade_hal_download_reboot_now

The following API will update the firmware and Factory reset the device in a single reboot.
1. fwupgrade_hal_update_and_factoryreset


3rd party vendors will implement appropriately to meet operational requirements. This interface is expected to block if the hardware is not ready.

## Threading Model

The interface is not thread safe.
Any module which is invoking the API should ensure calls are made in a thread safe manner.

Different 3rd party vendors allowed to create internal threads to meet the operational requirements. In this case 3rd party implementations should be responsible to synchronize between the calls, events and cleanup the thread.

## Process Model
All API's are expected to be called from multiple process.
## Memory Model

The client is responsible to allocate and de-allocate memory for necessary API's as specified in API documentation.
Different 3rd party vendors allowed to allocate memory for internal operational requirements. In this case 3rd party implementations should be responsible to de-allocate internally.

## Power Management Requirements

The HAL is not involved in any of the power management operation.
Any power management state transitions MUST not affect the operation of the HAL.

## Asynchronous Notification Model

There are no asynchronous notifications.

## Blocking calls

The API's are expected to work synchronously and should complete within a time period commensurate with the complexity of the operation and in accordance with any relevant specification.

Any calls that can fail due to the lack of a response should have a timeout period in accordance with any API documentation.

## Internal Error Handling

All the Firmware Management HAL API's should return error synchronously as a return argument. HAL is responsible to handle system errors(e.g. out of memory) internally.

## Persistence Model

There is no requirement for HAL to persist any setting information. The caller is responsible to persist any settings related to their implementation.

## Nonfunctional requirements

Following non functional requirement should be supported by the component.

## Logging and debugging requirements

The component is should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

The logging should be consistence across all HAL components.

If the vendor is going to log then it has to be logged in `xxx_vendor_hal.log` file name.

Logging should be defined with log levels as per Linux standard logging.

## Memory and performance requirements

The component should not contributing more to memory and CPU utilization while performing normal operations and commensurate with the operation required.

## Quality Control

Firmware Management HAL implementation should pass `Coverity`, `Black duck`, `Valgrind` checks without any issue.

There should not be any memory leaks/corruption introduced by HAL and underneath 3rd party software implementation.

## Licensing

Firmware Management HAL implementation is expected to released under the Apache License 2.0.

## Build Requirements

The source code should be build under Linux Yocto environment and should be delivered as a shared library named as `libfw_upgrade.so`

## Variability Management

Any new API introduced should be implemented by all the 3rd party module and RDK generic code should be compatible with specific version of HAL software.

Each API interface will be versioned using [Semantic Versioning 2.0.0](https://semver.org/), the vendor code will comply with a specific version of the interface.

## Platform or Product Customization

None

## Interface API Documentation

All HAL function prototypes and datatype definitions are available in `fwupgrade_hal.h` file.

  1.  Components/Processes must include `fwupgrade_hal.h` to make use of Firmware Management HAL capabilities.
  2.  Components/Processes should add linker dependency for `libfw_upgrade.so`


## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

### UML Diagrams

## Sequence Diagram

```mermaid
sequenceDiagram
participant Caller
participant FirmwareManagement HAL
participant Vendor
Note over Caller: Init once during bootup, Needed for Dependent API's. <br> Ignore this if caller doesn't have any Dependent API's
Caller->>FirmwareManagement HAL: fwupgrade_hal_set_download_url() and <br> fwupgrade_hal_set_download_interface()
FirmwareManagement HAL->>Vendor: 
Vendor ->>FirmwareManagement HAL: 
FirmwareManagement HAL->>Caller: return

Caller->>FirmwareManagement HAL: fwupgrade_hal_download()
FirmwareManagement HAL->>Vendor: 
Vendor ->>FirmwareManagement HAL: 
FirmwareManagement HAL->>Caller: return

Caller->>FirmwareManagement HAL: fwupgrade_hal_reboot_ready() and <br> fwupgrade_hal_download_reboot_now()
FirmwareManagement HAL->>Vendor: 
Vendor ->>FirmwareManagement HAL: 
FirmwareManagement HAL->>Caller: return
```
/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BLE_BUTTON_SERVICE_H__
#define __BLE_BUTTON_SERVICE_H__

Serial pc(USBTX,USBRX);

class ButtonService {
public:
    const static uint16_t BUTTON_SERVICE_UUID              = 0xA000;
    const static uint16_t BUTTON_STATE_CHARACTERISTIC_UUID = 0xA001;

    ButtonService(BLE &_ble, bool buttonPressedInitial) :
    ble(_ble), counter(new uint16_t(0)), buttonState(BUTTON_STATE_CHARACTERISTIC_UUID, counter, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&buttonState};
        GattService         buttonService(ButtonService::BUTTON_SERVICE_UUID, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        ble.gattServer().addService(buttonService);
    }

    void updateButtonState(bool newState) {
        if (newState) {
        *counter=(*counter)+1;
        pc.printf("%d", *counter);
        ble.gattServer().write(buttonState.getValueHandle(), (uint8_t *)counter, sizeof(uint16_t));
        }
    }

private:
    BLE                              &ble;
    uint16_t* counter;
    ReadOnlyGattCharacteristic<uint16_t>  buttonState;
};

#endif /* #ifndef __BLE_BUTTON_SERVICE_H__ */

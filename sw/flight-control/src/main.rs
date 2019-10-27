//! Blinks an LED
//!
//! This assumes that a LED is connected to pc13 as is the case on the blue pill board.
//!
//! Note: Without additional hardware, PC13 should not be used to drive an LED, see page 5.1.2 of
//! the reference manaual for an explanation. This is not an issue on the blue pill.

#![deny(unsafe_code)]
#![no_std]
#![no_main]

extern crate embedded_hal as hal;
extern crate stm32f1xx_hal;

use panic_halt as _;

use nb::block;

use stm32f1xx_hal::{
    prelude::*,
    pac,
    timer::Timer,
    spi::Spi
};
use cortex_m_rt::entry;
use embedded_hal::digital::v2::OutputPin;
use hal::blocking::spi;
use hal::spi::{Mode, Phase, Polarity};
use hal::blocking::i2c;

pub struct Mpu6050<SPI, NSS> {
    spi: SPI,
    nss: NSS,
}

#[derive(Clone, Copy)]
pub enum Register {
    BitFraming = 0x0d,
}

const R: u8 = 1 << 7;
const W: u8 = 0 << 7;

impl Register {
    pub fn read_address(&self) -> u8 {
        ((*self as u8) << 1) | R
    }

    pub fn write_address(&self) -> u8 {
        ((*self as u8) << 1) | W
    }
}

impl<E, NSS, SPI> Mpu6050<SPI, NSS>
where
    SPI: spi::Transfer<u8, Error = E> + spi::Write<u8, Error = E>,
    NSS: OutputPin,
{
    pub fn new(spi: SPI, nss: NSS) -> Self {
        let mut mpu = Mpu6050{spi, nss};
        mpu
    }

    fn with_nss_low<F, T>(&mut self, f: F) -> T
    where
        F: FnOnce(&mut Self) -> T,
    {
        self.nss.set_low();
        let result = f(self);
        self.nss.set_high();

        result
    }

    pub fn write(&mut self, reg: Register, val: u8) -> Result<(), E> {
        let reg = Register::BitFraming;
        let val: u8 = 5;
        self.with_nss_low(|mpu| mpu.spi.write(&[reg.write_address(), val]));
        Ok(())
    }
}

#[entry]
fn main() -> ! {
    let mode = Mode{
        polarity: Polarity::IdleLow,
        phase: Phase::CaptureOnFirstTransition,
    };

    // Get access to the core peripherals from the cortex-m crate
    let cp = cortex_m::Peripherals::take().unwrap();
    // Get access to the device specific peripherals from the peripheral access crate
    let dp = pac::Peripherals::take().unwrap();
    // Take ownership over the raw flash and rcc devices and convert them into the corresponding
    // HAL structs
    let mut flash = dp.FLASH.constrain();
    let mut rcc = dp.RCC.constrain();
    let mut afio = dp.AFIO.constrain(&mut rcc.apb2);
    // Acquire the GPIOC peripheral
    let mut gpioc = dp.GPIOC.split(&mut rcc.apb2);
    let mut gpioa = dp.GPIOA.split(&mut rcc.apb2);

    // Freeze the configuration of all the clocks in the system and store the frozen frequencies in
    // `clocks`
    let dma = dp.DMA1.split(&mut rcc.ahb);
    //rcc.apb1.modify(|_, w| w.time2en().set_bit());
    let clocks = rcc.cfgr.freeze(&mut flash.acr);

    // Configure gpio C pin 13 as a push-pull output. The `crh` register is passed to the function
    // in order to configure the port. For pins 0-7, crl should be passed instead.
    let mut led = gpioc.pc13.into_push_pull_output(&mut gpioc.crh);
    // Configure the syst timer to trigger an update every second
    let mut timer = Timer::syst(cp.SYST, &clocks);

    let mut sck = gpioa.pa5.into_alternate_push_pull(&mut gpioa.crl);
    let mut mosi = gpioa.pa7.into_alternate_push_pull(&mut gpioa.crl);
    let mut miso = gpioa.pa6;
    let mut spi = Spi::spi1(dp.SPI1, (sck, miso, mosi), &mut afio.mapr, mode, 1.mhz(), clocks, &mut rcc.apb2);

    let mut buffer = [0, 0];
    let mut nss = gpioa.pa4.into_push_pull_output(&mut gpioa.crl);
    //let mut mpu = Mpu6050::new(spi, nss);
    //mpu.write(Register::BitFraming, 0);

    // Wait for the timer to trigger an update and change the state of the LED
    loop {
        //block!(timer.wait()).unwrap();
        led.set_high().unwrap();
        //block!(timer.wait()).unwrap();
        led.set_low().unwrap();
    }
}

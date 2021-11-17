package com.cryptolabs.carexoid.github.binarypower;

import org.junit.jupiter.api.Test;

import java.math.BigInteger;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class BinaryPowerTest {

    @Test
    void zeroInPowerZeroShouldReturnOne() {
        assertEquals(BigInteger.ONE, BinaryPower.power(BigInteger.ZERO, 0));
    }

    @Test
    void negativeNumberShouldReturnNegativeForOddPower() {
        assertEquals(BigInteger.valueOf(-8), BinaryPower.power(BigInteger.valueOf(-2), 3));
    }

    @Test
    void negativeNumberShouldReturnPositiveForEvenPower() {
        assertEquals(BigInteger.valueOf(16), BinaryPower.power(BigInteger.valueOf(-2), 4));
    }

    @Test
    void negativePowerThrowsUnsupportedOperationException() {
        assertThrows(UnsupportedOperationException.class,
                () -> BinaryPower.power(BigInteger.ONE, -3),
                "Negative power unsupported");
    }

    @Test
    void resultsForPowerShouldBeSameAsLibPower() {
        BigInteger a;
        int power;
        Random rand = new Random();

        for (int i = 0; i < 100; i++) {
            a = BigInteger.valueOf(Math.abs(rand.nextInt()));
            power = Math.abs(rand.nextInt() % 1000);
            assertEquals(a.pow(power), BinaryPower.power(a, power));
        }
    }

}
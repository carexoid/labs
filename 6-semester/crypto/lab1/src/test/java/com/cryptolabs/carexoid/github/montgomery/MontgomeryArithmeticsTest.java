package com.cryptolabs.carexoid.github.montgomery;

import org.junit.jupiter.api.Test;

import java.math.BigInteger;

import static org.junit.jupiter.api.Assertions.*;

class MontgomeryArithmeticsTest {

    @Test
    void evenModuleThrowIllegalArgumentExceptionForMultiplying() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modMultiply(BigInteger.ONE, BigInteger.ONE, BigInteger.TWO),
                "Mod should be a positive odd number");
    }

    @Test
    void negativeModuleThrowIllegalArgumentExceptionForMultiplying() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modMultiply(BigInteger.ONE, BigInteger.ONE, BigInteger.valueOf(-1)),
                "Mod should be a positive odd number");
    }

    @Test
    void zeroModuleThrowIllegalArgumentExceptionForMultiplying() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modMultiply(BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO),
                "Mod should be a positive odd number");
    }

    @Test
    void evenModuleThrowIllegalArgumentExceptionForPower() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modPower(BigInteger.ONE, BigInteger.ONE, BigInteger.TWO),
                "Mod should be a positive odd number");
    }

    @Test
    void negativeModuleThrowIllegalArgumentExceptionForPower() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modPower(BigInteger.ONE, BigInteger.ONE, BigInteger.valueOf(-1)),
                "Mod should be a positive odd number");
    }

    @Test
    void zeroModuleThrowIllegalArgumentExceptionForPower() {
        assertThrows(IllegalArgumentException.class,
                () -> MontgomeryArithmetics.modPower(BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO),
                "Mod should be a positive odd number");
    }

    @Test
    void multiplyingResultShouldBeTheSameAsLib() {
        BigInteger a, b, n;

        a = new BigInteger("23456787654321");
        b = new BigInteger("4567890876543245");
        n = new BigInteger("34567898761");
        assertEquals(a.multiply(b).mod(n), MontgomeryArithmetics.modMultiply(a,b,n));
    }

    @Test
    void powerResultShouldBeTheSameAsLib() {
        BigInteger a, b, n;

        a = new BigInteger("23456787654321");
        b = new BigInteger("4567890876543245");
        n = new BigInteger("34567898761");
        assertEquals(a.modPow(b, n), MontgomeryArithmetics.modPower(a,b,n));
    }
}
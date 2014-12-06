static int writeI2C(Uint16 address, Uint16 *data, Uint16 quantity)
{
    CSL_Status status;

    if ((data != NULL)  && (quantity != 0))
    {
        status = Wire.beginTransmission(address);
        if (status == CSL_SOK)
        {
            status = Wire.write((unsigned int*)data, (unsigned int)quantity);
            if (status == quantity)
            {
                status = Wire.endTransmission();
            }
            else
            {
                status = CSL_ESYS_FAIL;
            }
        }
        else
        {
            status = CSL_ESYS_FAIL;
        }
    }
    else
    {
        status = CSL_ESYS_INVPARAMS;
    }

    csl_waitusec(0xFFF);

    return (status);
}

/** ===========================================================================
 *   @n@b rset
 *
 *   @b Description
 *   @n Function to send commands to codec.
 *
 *   @b Arguments
 *   @verbatim
 *      regnum    - Codec register number
 *      regval    - Value to be written
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - writes are successful
 *   @li                    CSL_ESYS_FAIL       - writes are not successful
 *
 *  ===========================================================================
 */
static int rset( Uint16 regnum, Uint16 regval )
{
    CSL_Status status;

    Uint16 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Device Register
    cmd[1] = regval;                // 8-bit Register Data

    status = writeI2C(I2C_CODEC_ADDR, cmd, 2);

    return (status);
}

static int readI2C(Uint16 address, Uint16 regnum, Uint16 *data, Uint16 quantity) //more general purpose I2C Readback function.
{
    CSL_Status status;
    Uint16     i2cWriteBuf[2];
    i2cWriteBuf[0] = regnum;

    status = Wire.requestFrom(address, quantity, (unsigned int *)i2cWriteBuf, 1);
    
    if (status != CSL_SOK) //check for bad transmission
    {
        Wire.endTransmission();
        Wire.begin();
        return (status);
    }

    for(int i = 0; (i < quantity) && Wire.available(); i++)
    {
      int value = Wire.read();
      data[i] = value;
    }
    return (status);
}

static int rget( Uint16 page, Uint16 regnum, Uint16 *regval) //AIC3204/6 specific register readback function.
{
    Wire.endTransmission();
    Wire.begin();
    CSL_Status status;

    Uint16 cmd;
 
    rset(0,page); //switch to the selected page.

    status = readI2C(I2C_CODEC_ADDR, regnum, regval, 1); //I2C_CODEC_ADDR

    return (status);
}


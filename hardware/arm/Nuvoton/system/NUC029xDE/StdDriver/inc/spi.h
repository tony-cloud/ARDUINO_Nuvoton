/**************************************************************************//**
 * @file     spi.h
 * @version  V3.0
 * $Revision: 7 $
 * $Date: 14/12/24 2:37p $
 * @brief    NUC029xDE Series SPI Driver Header File
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC029xDE_Device_Driver NUC029xDE Device Driver
  @{
*/

/** @addtogroup SPI_Driver SPI Driver
  @{
*/

/** @addtogroup SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/

#define SPI_MODE_0        (SPI_CNTRL_TX_NEG_Msk)                          /*!< CLKP=0; RX_NEG=0; TX_NEG=1 */
#define SPI_MODE_1        (SPI_CNTRL_RX_NEG_Msk)                          /*!< CLKP=0; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_2        (SPI_CNTRL_CLKP_Msk | SPI_CNTRL_RX_NEG_Msk)     /*!< CLKP=1; RX_NEG=1; TX_NEG=0 */
#define SPI_MODE_3        (SPI_CNTRL_CLKP_Msk | SPI_CNTRL_TX_NEG_Msk)     /*!< CLKP=1; RX_NEG=0; TX_NEG=1 */

#define SPI_SLAVE         (SPI_CNTRL_SLAVE_Msk)                           /*!< Set as slave */
#define SPI_MASTER        (0x0)                                           /*!< Set as master */

#define SPI_SS0               (1<<SPI_SSR_SSR_Pos)                        /*!< Select SPIn_SS0 */
#define SPI_SS_ACTIVE_HIGH    (SPI_SSR_SS_LVL_Msk)                        /*!< SS active high */
#define SPI_SS_ACTIVE_LOW     (0x0)                                       /*!< SS active low */

#define SPI_UNIT_INT_MASK                (0x01)                           /*!< Unit transfer interrupt mask */
#define SPI_SSTA_INT_MASK                (0x02)                           /*!< Slave 3-Wire mode start interrupt mask */
#define SPI_FIFO_TX_INT_MASK             (0x04)                           /*!< FIFO TX interrupt mask */
#define SPI_FIFO_RX_INT_MASK             (0x08)                           /*!< FIFO RX interrupt mask */
#define SPI_FIFO_RXOV_INT_MASK           (0x10)                           /*!< FIFO RX overrun interrupt mask */
#define SPI_FIFO_TIMEOUT_INT_MASK        (0x20)                           /*!< FIFO RX timeout interrupt mask */

#define SPI_BUSY_MASK                    (0x01)                           /*!< Busy status mask */
#define SPI_RX_EMPTY_MASK                (0x02)                           /*!< RX empty status mask */
#define SPI_RX_FULL_MASK                 (0x04)                           /*!< RX full status mask */
#define SPI_TX_EMPTY_MASK                (0x08)                           /*!< TX empty status mask */
#define SPI_TX_FULL_MASK                 (0x10)                           /*!< TX full status mask */

/*@}*/ /* end of group SPI_EXPORTED_CONSTANTS */


/** @addtogroup NUC131_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief      Abort the current transfer in Slave 3-wire mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set the SLV_ABORT bit of SPI_CNTRL2 register to abort the current transfer in Slave 3-wire mode.
  */
#define SPI_ABORT_3WIRE_TRANSFER(spi)   ((spi)->CNTRL2 |= SPI_CNTRL2_SLV_ABORT_Msk)

/**
  * @brief      Clear the Slave 3-wire mode start interrupt flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Write 1 to SLV_START_INTSTS bit of SPI_STATUS register to clear the Slave 3-wire mode start interrupt flag.
  */
#define SPI_CLR_3WIRE_START_INT_FLAG(spi)   ((spi)->STATUS = SPI_STATUS_SLV_START_INTSTS_Msk)

/**
  * @brief      Clear the unit transfer interrupt flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Write 1 to IF bit of SPI_STATUS register to clear the unit transfer interrupt flag.
  */
#define SPI_CLR_UNIT_TRANS_INT_FLAG(spi)   ((spi)->STATUS = SPI_STATUS_IF_Msk)

/**
  * @brief      Disable Slave 3-wire mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear NOSLVSEL bit of SPI_CNTRL2 register to disable Slave 3-wire mode.
  */
#define SPI_DISABLE_3WIRE_MODE(spi)   ((spi)->CNTRL2 &= ~SPI_CNTRL2_NOSLVSEL_Msk)

/**
  * @brief      Disable Dual I/O mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear DUAL_IO_EN bit of SPI_CNTRL2 register to disable Dual I/O mode.
  */
#define SPI_DISABLE_DUAL_MODE(spi)   ((spi)->CNTRL2 &= ~SPI_CNTRL2_DUAL_IO_EN_Msk)

/**
  * @brief      Enable Slave 3-wire mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set NOSLVSEL bit of SPI_CNTRL2 register to enable Slave 3-wire mode.
  */
#define SPI_ENABLE_3WIRE_MODE(spi)   ((spi)->CNTRL2 |= SPI_CNTRL2_NOSLVSEL_Msk)

/**
  * @brief      Enable Dual input mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear DUAL_IO_DIR bit and set DUAL_IO_EN bit of SPI_CNTRL2 register to enable Dual input mode.
  */
#define SPI_ENABLE_DUAL_INPUT_MODE(spi)   ((spi)->CNTRL2 = ((spi)->CNTRL2 & (~SPI_CNTRL2_DUAL_IO_DIR_Msk)) | SPI_CNTRL2_DUAL_IO_EN_Msk)

/**
  * @brief      Enable Dual output mode.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set DUAL_IO_DIR bit and DUAL_IO_EN bit of SPI_CNTRL2 register to enable Dual output mode.
  */
#define SPI_ENABLE_DUAL_OUTPUT_MODE(spi)   ((spi)->CNTRL2 |= (SPI_CNTRL2_DUAL_IO_EN_Msk | SPI_CNTRL2_DUAL_IO_DIR_Msk))

/**
  * @brief      Get the count of available data in RX FIFO.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     The count of available data in RX FIFO.
  * @details    Read RX_FIFO_COUNT (SPI_STATUS[15:12]) to get the count of available data in RX FIFO.
  */
#define SPI_GET_RX_FIFO_COUNT(spi)   (((spi)->STATUS & SPI_STATUS_RX_FIFO_COUNT_Msk) >> SPI_STATUS_RX_FIFO_COUNT_Pos)

/**
  * @brief      Get the RX FIFO empty flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 RX FIFO is not empty.
  * @retval     1 RX FIFO is empty.
  * @details    Read RX_EMPTY bit of SPI_STATUS register to get the RX FIFO empty flag.
  */
#define SPI_GET_RX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_RX_EMPTY_Msk)>>SPI_STATUS_RX_EMPTY_Pos)

/**
  * @brief      Get the TX FIFO empty flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 TX FIFO is not empty.
  * @retval     1 TX FIFO is empty.
  * @details    Read TX_EMPTY bit of SPI_STATUS register to get the TX FIFO empty flag.
  */
#define SPI_GET_TX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TX_EMPTY_Msk)>>SPI_STATUS_TX_EMPTY_Pos)

/**
  * @brief      Get the TX FIFO full flag.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 TX FIFO is not full.
  * @retval     1 TX FIFO is full.
  * @details    Read TX_FULL bit of SPI_STATUS register to get the TX FIFO full flag.
  */
#define SPI_GET_TX_FIFO_FULL_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TX_FULL_Msk)>>SPI_STATUS_TX_FULL_Pos)

/**
  * @brief      Get the datum read from RX register.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     Data in RX register.
  * @details    Read SPI_RX register to get the received datum.
  */
#define SPI_READ_RX(spi)   ((spi)->RX)

/**
  * @brief      Write datum to TX register.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32TxData The datum which user attempt to transfer through SPI bus.
  * @return     None.
  * @details    Write u32TxData to TX register.
  */
#define SPI_WRITE_TX(spi, u32TxData)   ((spi)->TX = (u32TxData))

/**
  * @brief      Set SPIn_SS0 pin to high state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIn_SS0 pin to high state.
  */
#define SPI_SET_SS0_HIGH(spi)   ((spi)->SSR = ((spi)->SSR & (~SPI_SSR_AUTOSS_Msk)) | (SPI_SSR_SS_LVL_Msk | SPI_SS0))

/**
  * @brief      Set SPIn_SS0 pin to low state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIn_SS0 pin to low state.
  */
#define SPI_SET_SS0_LOW(spi)   ((spi)->SSR = ((spi)->SSR & (~(SPI_SSR_AUTOSS_Msk|SPI_SSR_SS_LVL_Msk))) | SPI_SS0)

/**
  * @brief      Enable Byte Reorder function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set REORDER bit of SPI_CNTRL register to enable Byte Reorder function.
  */
#define SPI_ENABLE_BYTE_REORDER(spi)   ((spi)->CNTRL |= SPI_CNTRL_REORDER_Msk)

/**
  * @brief      Disable Byte Reorder function.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear REORDER bit of SPI_CNTRL register to disable Byte Reorder function.
  */
#define SPI_DISABLE_BYTE_REORDER(spi)   ((spi)->CNTRL &= ~SPI_CNTRL_REORDER_Msk)

/**
  * @brief      Set the length of suspend interval.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32SuspCycle Decides the length of suspend interval. It could be 0 ~ 15.
  * @return     None.
  * @details    Set the length of suspend interval according to u32SuspCycle.
  *             The length of suspend interval is ((u32SuspCycle + 0.5) * the length of one SPI bus clock cycle).
  */
#define SPI_SET_SUSPEND_CYCLE(spi, u32SuspCycle)   ((spi)->CNTRL = ((spi)->CNTRL & ~SPI_CNTRL_SP_CYCLE_Msk) | ((u32SuspCycle) << SPI_CNTRL_SP_CYCLE_Pos))

/**
  * @brief      Set the SPI transfer sequence with LSB first.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Set LSB bit of SPI_CNTRL register to set the SPI transfer sequence with LSB first.
  */
#define SPI_SET_LSB_FIRST(spi)   ((spi)->CNTRL |= SPI_CNTRL_LSB_Msk)

/**
  * @brief      Set the SPI transfer sequence with MSB first.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    Clear LSB bit of SPI_CNTRL register to set the SPI transfer sequence with MSB first.
  */
#define SPI_SET_MSB_FIRST(spi)   ((spi)->CNTRL &= ~SPI_CNTRL_LSB_Msk)

/**
  * @brief      Set the data width of a SPI transaction.
  * @param[in]  spi The pointer of the specified SPI module.
  * @param[in]  u32Width The bit width of transfer data.
  * @return     None.
  * @details    The data width can be 8 ~ 32 bits.
  */
#define SPI_SET_DATA_WIDTH(spi, u32Width)   ((spi)->CNTRL = ((spi)->CNTRL & ~SPI_CNTRL_TX_BIT_LEN_Msk) | (((u32Width)&0x1F) << SPI_CNTRL_TX_BIT_LEN_Pos))

/**
  * @brief      Get the SPI busy state.
  * @param[in]  spi The pointer of the specified SPI module.
  * @retval     0 SPI controller is not busy.
  * @retval     1 SPI controller is busy.
  * @details    This macro will return the busy state of SPI controller.
  */
#define SPI_IS_BUSY(spi)   ( ((spi)->CNTRL & SPI_CNTRL_GO_BUSY_Msk)>>SPI_CNTRL_GO_BUSY_Pos )

/**
  * @brief      Set the GO_BUSY bit to trigger SPI transfer.
  * @param[in]  spi The pointer of the specified SPI module.
  * @return     None.
  * @details    If FIFO mode is disabled, user can use this macro to trigger the data transfer after all configuration is ready.
  *             If FIFO mode is enabled, user should not use this macro to trigger the data transfer. SPI controller will trigger the data transfer
  *             automatically after user write to SPI_TX register.
  */
#define SPI_TRIGGER(spi)   ((spi)->CNTRL |= SPI_CNTRL_GO_BUSY_Msk)



/* Function prototype declaration */
uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_EnableFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
void SPI_DisableFIFO(SPI_T *spi);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask);
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask);



/**
  * @} End of SPI Device Function Interface
  */

/**
  * @} End of NUC029xDE Function Interface
  */


#ifdef __cplusplus
}
#endif

#endif


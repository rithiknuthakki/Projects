# Algorithmic Trading System

A C++ implementation of an algorithmic trading system covering both trading decision-making and trade execution. The project is divided into two phases, progressing from order-book processing and arbitrage detection to market simulation and order execution.

## Phase 1 – Order Book Processing and Arbitrage Detection

Developed the core trading decision layer of an algorithmic trading system in C++. Built an order book to continuously process incoming buy and sell orders, including orders involving linear combinations of multiple stocks.

Implemented arbitrage detection to identify combinations of available orders that generate positive profit while maintaining a zero net position across all stocks. The system evaluates available orders and identifies profitable combinations of trades without retaining market exposure.

Extended the implementation to support order quantities (lots), allowing arbitrage opportunities to be identified across multiple units and partial quantities of orders. Also implemented order updates and cancellations, ensuring that remaining quantities and outstanding orders were correctly maintained as new market orders arrived.

This phase established the core infrastructure for processing market data, maintaining the order book, and identifying profitable arbitrage opportunities before introducing the trade execution layer.

## Phase 2 – Market Simulation and Trade Execution

In Phase 2, implemented the execution layer of the algorithmic trading system by building a simulated market and matching engine. The market processes incoming orders from multiple participants, maintains active orders along with their price, quantity, timestamp, and expiry information, and executes compatible buy and sell orders based on the required matching priorities.

A key part of the implementation was handling partial order matching and order-book updates. When an order was only partially fulfilled, the remaining quantity was retained in the order book and made available for subsequent matches. Orders were also correctly removed when they were fully executed or expired, ensuring that the state of the market remained consistent as new orders arrived and trades were executed.

On top of the simulated market, integrated the trading logic by combining the arbitrage detection strategy from Phase 1 with a market-making strategy based on moving median prices. The trader could participate in the market by placing its own orders while accounting for order expiry and ensuring that it did not create self-arbitrage opportunities.

This phase connected the trading strategies developed earlier with an actual market simulation, bringing together order processing, matching, execution, expiry management, and trading decision-making in a continuously changing market environment.

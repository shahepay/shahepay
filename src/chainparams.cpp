// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The Shahepay Core developers

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>
#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 3162191751 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "shahepay to moneta dla wszystkich ludzi";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {consensus.nSegwitEnabled = false;}

void CChainParams::TurnOffCSV() {consensus.nCSVEnabled = false;}

void CChainParams::TurnOffBIP34() {consensus.nBIP34Enabled = false;}

void CChainParams::TurnOffBIP65() {consensus.nBIP65Enabled = false;}

void CChainParams::TurnOffBIP66() {consensus.nBIP66Enabled = false;}

bool CChainParams::BIP34() {return consensus.nBIP34Enabled;}

bool CChainParams::BIP65() {return consensus.nBIP34Enabled;}

bool CChainParams::BIP66() {return consensus.nBIP34Enabled;}

bool CChainParams::CSVEnabled() const{return consensus.nCSVEnabled;}


/** MAIN NETWORK **/

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 2100000;
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
	consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1613;
        consensus.nMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;

        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1646929722;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1814;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1646929722;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1714;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;

        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1646929722;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;

        consensus.nMinimumChainWork = uint256S("0x00");

        consensus.defaultAssumeValid = uint256S("0x000000cba50260c77ad344051a00d477bc6159a2426e94ff62b0a9173f00ef82"); // Block 1

        pchMessageStart[0] = 63; // S
        pchMessageStart[1] = 40; // H
        pchMessageStart[2] = 23; // A
        pchMessageStart[3] = 42; // H or J
        nDefaultPort = 56789;
        nPruneAfterHeight = 1000000;


        // Build Genesis Block:
        /*
        uint32_t nGenesisTime = ;
        arith_uint256 test;
        bool fNegative;
        bool fOverflow;
        test.SetCompact(0x1e00ffff, &fNegative, &fOverflow);
        std::cout << "Test threshold: " << test.GetHex() << "\n\n";
        int genesisNonce = 0;
        uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        for (int i=0;i<40000000;i++) {
            genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e00ffff, 2, 500 * COIN);
            //genesis.hashPrevBlock = TempHashHolding;
            consensus.hashGenesisBlock = genesis.GetHash();
            arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
            if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
                BestBlockHash = consensus.hashGenesisBlock;
                std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
                std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        	std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        	std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        	std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;
            }
            TempHashHolding = consensus.hashGenesisBlock;
            if (BestBlockHashArith < test) {
                genesisNonce = i - 1;
                break;
            }
            //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        std::cout << "Genesis Merkle " << genesis.hashMerkleRoot.GetHex() << std::endl;
        std::cout << "\n";
        return;
        */

        genesis = CreateGenesisBlock(1646929722, 7765368, 0x1e00ffff, 2, 500 * COIN);

        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000cba50260c77ad344051a00d477bc6159a2426e94ff62b0a9173f00ef82"));
        assert(genesis.hashMerkleRoot == uint256S("0c402877080e148835778c5ea545748e3ac372a9afe247e866d39e2cc9265e2e"));

        // Main Seeders
	vSeeds.emplace_back("dnsseed.shahepay.com", true);

	// Backup Seeders
    	vSeeds.emplace_back("135.125.225.55", true);
	vSeeds.emplace_back("51.195.249.132", true);
	vSeeds.emplace_back("135.125.225.55", true);


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60); // R
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,30); // D
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128); // C
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {

            }
        };

        chainTxData = ChainTxData{

        };

        /** SHAHE Start **/
         // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "SDissueAssetXXXXXXXXXXXXXXXXarpEmt";
        strReissueAssetBurnAddress = "SDReissueAssetXXXXXXXXXXXXXXZAKPbJ";
        strIssueSubAssetBurnAddress = "SDissueSubAssetXXXXXXXXXXXXXW6D3dn";
        strIssueUniqueAssetBurnAddress = "SDissueUniqueAssetXXXXXXXXXXSkWCDd";
        strIssueMsgChannelAssetBurnAddress = "SDissueMsgChanneLAssetXXXXXXSkQjob";
        strIssueQualifierAssetBurnAddress = "SDissueQuaLifierXXXXXXXXXXXXZVc7zN";
        strIssueSubQualifierAssetBurnAddress = "SDissueSubQuaLifierXXXXXXXXXUhKn5T";
        strIssueRestrictedAssetBurnAddress = "SDissueRestrictedXXXXXXXXXXXXveZHA";
        strAddNullQualifierTagBurnAddress = "SDaddTagBurnXXXXXXXXXXXXXXXXaqLzue";

            //Global Burn Address
        strGlobalBurnAddress = "SDBurnXXXXXXXXXXXXXXXXXXXXXXWdW4er";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours

        nAssetActivationHeight = 100000; // Asset activated block height
        nMessagingActivationBlock = 100000; // Messaging activated block height
        nRestrictedActivationBlock = 100000; // Restricted activated block height
        /** SHAHE End **/
    }
};


/**  TESTNET **/

class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2100000;
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;

        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60;
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1310;
        consensus.nMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1645757351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 1645757351;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 1310;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 2016;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 1645757351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 1677293351;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 1411;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 2016;

        consensus.nMinimumChainWork = uint256S("0x00");

        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xe4; // R
        pchMessageStart[1] = 0xa1; // V
        pchMessageStart[2] = 0xa3; // N
        pchMessageStart[3] = 0x54; // T
        nDefaultPort = 16789;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1645757351;

        genesis = CreateGenesisBlock(1645757351, 24232574, 0x1e00ffff, 2, 500 * COIN);

        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000308ac9641625ca3bd67b36985364c54c39c74e3b5cf9de262065b408d7"));
        assert(genesis.hashMerkleRoot == uint256S("0c402877080e148835778c5ea545748e3ac372a9afe247e866d39e2cc9265e2e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,90);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{

        };

        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        strIssueAssetBurnAddress = "sXissueAssetXXXXXXXXXXXXXXXXZbEEFU";
        strReissueAssetBurnAddress = "sXReissueAssetXXXXXXXXXXXXXXYSUun2";
        strIssueSubAssetBurnAddress = "sXissueSubAssetXXXXXXXXXXXXXakqJkC";
        strIssueUniqueAssetBurnAddress = "sXissueUniqueAssetXXXXXXXXXXSycUW7";
        strIssueMsgChannelAssetBurnAddress = "sXissueMsgChanneLAssetXXXXXXRjh85D";
        strIssueQualifierAssetBurnAddress = "sXissueQuaLifierXXXXXXXXXXXXXAGDbp";
        strIssueSubQualifierAssetBurnAddress = "sXissueSubQuaLifierXXXXXXXXXXB1EjR";
        strIssueRestrictedAssetBurnAddress = "sXissueRestrictedXXXXXXXXXXXb6ZKVu";
        strAddNullQualifierTagBurnAddress = "sXaddTagBurnXXXXXXXXXXXXXXXXWYBj2e";

        strGlobalBurnAddress = "sXBurnXXXXXXXXXXXXXXXXXXXXXXX3XqfT";

        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60;
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12;

        nAssetActivationHeight = 0;
        nMessagingActivationBlock = 0;
        nRestrictedActivationBlock = 0;

    }
};


/**  REGRESSION TEST **/

class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true;
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60;
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_MSG_REST_ASSETS].nOverrideMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].bit = 8;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideRuleChangeActivationThreshold = 108;
        consensus.vDeployments[Consensus::DEPLOYMENT_ENFORCE_VALUE].nOverrideMinerConfirmationWindow = 144;

        consensus.nMinimumChainWork = uint256S("0x00");

        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xc6; // C
        pchMessageStart[1] = 0xfe; // R
        pchMessageStart[2] = 0xaf; // O
        pchMessageStart[3] = 0x8c; // W
        nDefaultPort = 26789;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1645757351, 24232574, 0x1e00ffff, 2, 500 * COIN);

        consensus.hashGenesisBlock = genesis.GetX16RHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000000308ac9641625ca3bd67b36985364c54c39c74e3b5cf9de262065b408d7"));
        assert(genesis.hashMerkleRoot == uint256S("0c402877080e148835778c5ea545748e3ac372a9afe247e866d39e2cc9265e2e"));


        vFixedSeeds.clear();
        vSeeds.clear();

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;
        nIssueMsgChannelAssetBurnAmount = 100 * COIN;
        nIssueQualifierAssetBurnAmount = 1000 * COIN;
        nIssueSubQualifierAssetBurnAmount = 100 * COIN;
        nIssueRestrictedAssetBurnAmount = 1500 * COIN;
        nAddNullQualifierTagBurnAmount = .1 * COIN;

        strIssueAssetBurnAddress = "r2issueAssetXXXXXXXXXXXXXXXXbfbi47";
        strReissueAssetBurnAddress = "r2ReissueAssetXXXXXXXXXXXXXXTxxPkJ";
        strIssueSubAssetBurnAddress = "r2issueSubAssetXXXXXXXXXXXXXVw16Ye";
        strIssueUniqueAssetBurnAddress = "r2issueUniqueAssetXXXXXXXXXXWmN3Qg";
        strIssueMsgChannelAssetBurnAddress = "r2issueMsgChanneLAssetXXXXXXW6188u";
        strIssueQualifierAssetBurnAddress = "r2issueQuaLifierXXXXXXXXXXXXVQXVcN";
        strIssueSubQualifierAssetBurnAddress = "r2issueSubQuaLifierXXXXXXXXXUAFxve";
        strIssueRestrictedAssetBurnAddress = "r1issueRestrictedXXXXXXXXXXXXZVT9V";
        strAddNullQualifierTagBurnAddress = "r2addTagBurnXXXXXXXXXXXXXXXXWQj6Et";

        strGlobalBurnAddress = "r2BurnXXXXXXXXXXXXXXXXXXXXXXV3KNcW";

        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60;
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12;

        nAssetActivationHeight = 0;
        nMessagingActivationBlock = 0;
        nRestrictedActivationBlock = 0;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &GetParams() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network, bool fForceBlockNetwork)
{
    SelectBaseParams(network);
    if (fForceBlockNetwork) {
        bNetwork.SetNetwork(network);
    }
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
	globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
	globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
	globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
	globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
	globalChainParams->TurnOffBIP66();
}

// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The shahepay Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SHAHEPAY_QT_SHAHEPAYADDRESSVALIDATOR_H
#define SHAHEPAY_QT_SHAHEPAYADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class shahepayAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit shahepayAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** shahepay address widget validator, checks for a valid shahepay address.
 */
class shahepayAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit shahepayAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SHAHEPAY_QT_SHAHEPAYADDRESSVALIDATOR_H

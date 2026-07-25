#!/bin/bash

# SPDX-FileCopyrightText: 2025 All contributors
#
# SPDX-License-Identifier: GPL-2.0-or-later

if [[ "$(which pre-commit)" == "" ]]; then
    pip install --user pre-commit
fi
pre-commit install

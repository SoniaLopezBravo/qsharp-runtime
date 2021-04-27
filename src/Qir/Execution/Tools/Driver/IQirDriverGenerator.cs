﻿// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System.IO;
using System.Threading.Tasks;
using Microsoft.Quantum.QsCompiler.BondSchemas.EntryPoint;

namespace Microsoft.Quantum.Qir.Tools.Driver
{
    public interface IQirDriverGenerator
    {
        Task GenerateAsync(EntryPointOperation entryPoint, Stream stream);

        string GetCommandLineArguments(EntryPointOperation entryPoint);
    }
}
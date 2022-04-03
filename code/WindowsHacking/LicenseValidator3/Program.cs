using System;

namespace LicenseValidator3
{
    using System;
    using System.IO;
    using System.Security.Cryptography;

    class Program
    {
        private const string LicenseKey = "McYyw+Of4njy9SvWjbaT8nzWqJ07i3BLzf7+aikVUN7gVkn4nSuWDKb1LNM6lFlO";
        private static readonly byte[] AESKey = System.Text.Encoding.UTF8.GetBytes("HelloWorld123456");
        public static byte[] EncryptStringToBytes_Aes(string plainText, byte[] Key)
        {
            // Check arguments.
            if (plainText == null || plainText.Length <= 0)
                throw new ArgumentNullException("plainText");
            if (Key == null || Key.Length <= 0)
                throw new ArgumentNullException("Key");
            byte[] encrypted;

            // Create an Aes object
            // with the specified key and IV.
            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = Key;
                aesAlg.Mode = CipherMode.ECB;

                // Create an encryptor to perform the stream transform.
                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, null);

                // Create the streams used for encryption.
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            //Write all data to the stream.
                            swEncrypt.Write(plainText);
                        }
                        encrypted = msEncrypt.ToArray();
                    }
                }
            }

            // Return the encrypted bytes from the memory stream.
            return encrypted;
        }
        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine($"Usage: LicenseValidator3.exe <license key>");
                return;
            }
            Console.WriteLine("Validating license key");

            var encryptedData = EncryptStringToBytes_Aes(args[0], Program.AESKey);
            var b64data = System.Convert.ToBase64String(encryptedData);

            if (b64data == LicenseKey)
            {
                Console.WriteLine("Validated successfully");
                return;
            }
            Console.WriteLine("Failed to validate license key");
            return;
        }
    }
}

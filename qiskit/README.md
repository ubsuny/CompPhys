# How to setup the IBM quantum API key in your codespace

To access the IBM quantum framework one has to use the API key found in your [profile settings](https://quantum-computing.ibm.com/account) in the IBM Quantumplatform.

Do *NOT* copy this key into a Jupyter notebook or any file in a githuib repository. If you publish it the whole world will be able to use your key!

Instead use a [codespace secret](https://docs.github.com/en/codespaces/managing-your-codespaces/managing-your-account-specific-secrets-for-github-codespaces) to access it.

Details can be found in the above link but in short do the following:

1. In the upper-right corner of any page on GitHub, click your profile photo, then click Settings.

2. In the "Code, planning, and automation" section of the sidebar, click  Codespaces.

3. To the right of "Codespaces secrets", click New secret.

4. Under "Name," type a name for your secret, use *IBMQUANTUM*.

5. Under "Value", copy the API key from your IBM quantum profile.

6. Select the "Repository access" drop-down menu, then click a repository you want to have access to the secret. Repeat for every repository you want to have access to the secret.


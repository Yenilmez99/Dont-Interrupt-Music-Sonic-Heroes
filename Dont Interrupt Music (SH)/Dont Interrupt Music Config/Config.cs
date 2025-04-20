using System.ComponentModel;
using Dont_Interrupt_Music_Config.Template.Configuration;
using Reloaded.Mod.Interfaces.Structs;

namespace Dont_Interrupt_Music_Config.Configuration
{
    public class Config : Configurable<Config>
    {
        /*
            User Properties:
                - Please put all of your configurable properties here.
    
            By default, configuration saves as "Config.json" in mod user config folder.    
            Need more config files/classes? See Configuration.cs
    
            Available Attributes:
            - Category
            - DisplayName
            - Description
            - DefaultValue

            // Technically Supported but not Useful
            - Browsable
            - Localizable

            The `DefaultValue` attribute is used as part of the `Reset` button in Reloaded-Launcher.
        */

        [Category("Mod Works on These Teams:")]
        [DisplayName("Team Sonic")]
        [DefaultValue(true)]
        public bool TeamSonic { get; set; } = true;

        [Category("Mod Works on These Teams:")]
        [DisplayName("Team Dark")]
        [DefaultValue(true)]
        public bool TeamDark { get; set; } = true;

        [Category("Mod Works on These Teams:")]
        [DisplayName("Team Rose")]
        [DefaultValue(false)]
        public bool TeamRose { get; set; } = false;

        [Category("Mod Works on These Teams:")]
        [DisplayName("Team Chaotix")]
        [DefaultValue(false)]
        public bool TeamChaotix { get; set; } = false;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Seaside Hill")]
        [DefaultValue(true)]
        public bool SeasideHill { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Ocean Place")]
        [DefaultValue(true)]
        public bool OceanPlace { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Grand Metropolis")]
        [DefaultValue(true)]
        public bool GrandMetropolis { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Power Plant")]
        [DefaultValue(true)]
        public bool PowerPlant { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Casino Park")]
        [DefaultValue(true)]
        public bool CasinoPark { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Bingo Highway")]
        [DefaultValue(true)]
        public bool BingoHighway { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Rail Canyon")]
        [DefaultValue(true)]
        public bool RailCanyon { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Bullet Station")]
        [DefaultValue(true)]
        public bool BulletStation { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Frog Forest")]
        [DefaultValue(true)]
        public bool FrogForest { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Lost Jungle")]
        [DefaultValue(true)]
        public bool LostJungle { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Hang Castle")]
        [DefaultValue(false)]
        public bool HangCastle { get; set; } = false;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Mystic Mansion")]
        [DefaultValue(false)]
        public bool MysticMansion { get; set; } = false;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Egg Fleet")]
        [DefaultValue(true)]
        public bool EggFleet { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("Final Fortress")]
        [DefaultValue(true)]
        public bool FinalFortress { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("EGG HAWK")]
        [DefaultValue(true)]
        public bool EGGHAWK { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("TEAM ?? 1")]
        [DefaultValue(true)]
        public bool TEAMVS1 { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("ROBOT CARNIVAL")]
        [DefaultValue(true)]
        public bool ROBOTCARNIVAL { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("EGG ALBATROS")]
        [DefaultValue(true)]
        public bool EGGALBATROS { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("TEAM ?? 2")]
        [DefaultValue(true)]
        public bool TEAMVS2 { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("ROBOT STORM")]
        [DefaultValue(true)]
        public bool ROBOTSTORM { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("EGG EMPEROR")]
        [DefaultValue(true)]
        public bool EGGEMPEROR { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("METAL MADNESS")]
        [DefaultValue(true)]
        public bool METALMADNESS { get; set; } = true;

        [Category("Mod Works on These Stages:")]
        [DisplayName("METAL SONIC")]
        [DefaultValue(true)]
        public bool METALSONIC { get; set; } = true;
    }

    /// <summary>
    /// Allows you to override certain aspects of the configuration creation process (e.g. create multiple configurations).
    /// Override elements in <see cref="ConfiguratorMixinBase"/> for finer control.
    /// </summary>
    public class ConfiguratorMixin : ConfiguratorMixinBase
    {
        // 
    }
}
